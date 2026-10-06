"""
Serial CSV Logger - Tkinter
Legge righe di dati da un Arduino via seriale e le salva in un file CSV.

Requisiti:  pip install pyserial

Formato atteso dall'Arduino: una riga per campione, valori separati da
virgola (o dal separatore impostato sotto), terminata da '\n'.
Esempio:  23.5,512,1
"""

import csv
import os
import queue
import threading
import time
from datetime import datetime
import tkinter as tk
from tkinter import ttk, filedialog, messagebox

import serial
import serial.tools.list_ports

# --------------------------------------------------------------------------
# CONFIGURAZIONE (valori di default, modificabili anche dalla GUI)
# --------------------------------------------------------------------------
DEFAULT_BAUD = 9600
BAUD_RATES = [9600, 19200, 38400, 57600, 115200, 230400, 250000, 500000]
INPUT_SEPARATOR = ","          # separatore usato dall'Arduino
CSV_DELIMITER = ";"            # ";" comodo per Excel in italiano, "," altrimenti
DEFAULT_HEADER = "valore1,valore2,valore3"   # nomi colonne (separati da virgola)
ADD_TIMESTAMP = True           # aggiunge colonna data/ora
ADD_ELAPSED = True             # aggiunge colonna secondi dall'avvio
SKIP_FIRST_LINES = 1           # scarta le prime N righe (spesso troncate al reset)
FLUSH_EVERY = 10               # flush su disco ogni N righe
MAX_LOG_LINES = 500            # righe mantenute nel monitor a video
SERIAL_TIMEOUT = 0.5           # s
DEFAULT_FILENAME = "dati_{:%Y%m%d_%H%M%S}.csv"
# --------------------------------------------------------------------------


class SerialReader(threading.Thread):
    """Thread che legge righe dalla seriale e le mette in una coda."""

    def __init__(self, port, baud, out_queue):
        super().__init__(daemon=True)
        self.port = port
        self.baud = baud
        self.q = out_queue
        self._stop_evt = threading.Event()
        self.ser = None

    def run(self):
        try:
            self.ser = serial.Serial(self.port, self.baud, timeout=SERIAL_TIMEOUT)
            # L'apertura della porta resetta la maggior parte degli Arduino
            time.sleep(2)
            self.ser.reset_input_buffer()
            self.q.put(("status", f"Connesso a {self.port} @ {self.baud}"))
        except serial.SerialException as e:
            self.q.put(("error", f"Impossibile aprire {self.port}: {e}"))
            return

        skipped = 0
        while not self._stop_evt.is_set():
            try:
                raw = self.ser.readline()
            except serial.SerialException as e:
                self.q.put(("error", f"Errore seriale: {e}"))
                break
            if not raw:
                continue
            line = raw.decode("utf-8", errors="replace").strip()
            if not line:
                continue
            if skipped < SKIP_FIRST_LINES:
                skipped += 1
                continue
            self.q.put(("data", line))

        try:
            if self.ser and self.ser.is_open:
                self.ser.close()
        except Exception:
            pass
        self.q.put(("closed", None))

    def stop(self):
        self._stop_evt.set()


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Arduino → CSV Logger")
        self.geometry("720x520")
        self.minsize(600, 400)

        self.q = queue.Queue()
        self.reader = None
        self.csv_file = None
        self.csv_writer = None
        self.logging = False
        self.rows_written = 0
        self.t0 = None

        self._build_ui()
        self._setup_clipboard()
        self.refresh_ports()
        self.protocol("WM_DELETE_WINDOW", self.on_close)
        self.after(50, self.process_queue)

    # ---------------------------------------------------------------- UI
    def _build_ui(self):
        pad = {"padx": 5, "pady": 4}

        # --- Connessione
        conn = ttk.LabelFrame(self, text="Connessione")
        conn.pack(fill="x", **pad)

        ttk.Label(conn, text="Porta:").grid(row=0, column=0, sticky="w", **pad)
        self.port_var = tk.StringVar()
        self.port_cb = ttk.Combobox(conn, textvariable=self.port_var, width=30, state="readonly")
        self.port_cb.grid(row=0, column=1, sticky="w", **pad)
        ttk.Button(conn, text="Aggiorna", command=self.refresh_ports).grid(row=0, column=2, **pad)

        ttk.Label(conn, text="Baud:").grid(row=0, column=3, sticky="w", **pad)
        self.baud_var = tk.IntVar(value=DEFAULT_BAUD)
        ttk.Combobox(conn, textvariable=self.baud_var, values=BAUD_RATES, width=8).grid(
            row=0, column=4, **pad)

        self.connect_btn = ttk.Button(conn, text="Connetti", command=self.toggle_connection)
        self.connect_btn.grid(row=0, column=5, **pad)

        # --- File CSV
        filef = ttk.LabelFrame(self, text="File CSV")
        filef.pack(fill="x", **pad)
        filef.columnconfigure(1, weight=1)

        ttk.Label(filef, text="File:").grid(row=0, column=0, sticky="w", **pad)
        self.file_var = tk.StringVar(
            value=os.path.join(os.getcwd(), DEFAULT_FILENAME.format(datetime.now())))
        self.file_entry = ttk.Entry(filef, textvariable=self.file_var)
        self.file_entry.grid(row=0, column=1, sticky="ew", **pad)
        ttk.Button(filef, text="Sfoglia…", command=self.choose_file).grid(row=0, column=2, **pad)

        ttk.Label(filef, text="Intestazione:").grid(row=1, column=0, sticky="w", **pad)
        self.header_var = tk.StringVar(value=DEFAULT_HEADER)
        self.header_entry = ttk.Entry(filef, textvariable=self.header_var)
        self.header_entry.grid(row=1, column=1, sticky="ew", **pad)

        opts = ttk.Frame(filef)
        opts.grid(row=2, column=0, columnspan=3, sticky="w")
        self.ts_var = tk.BooleanVar(value=ADD_TIMESTAMP)
        self.el_var = tk.BooleanVar(value=ADD_ELAPSED)
        self.append_var = tk.BooleanVar(value=False)
        # Widget da bloccare durante la registrazione
        self.lock_widgets = [
            ttk.Checkbutton(opts, text="Timestamp", variable=self.ts_var),
            ttk.Checkbutton(opts, text="Secondi trascorsi", variable=self.el_var),
            ttk.Checkbutton(opts, text="Accoda a file esistente", variable=self.append_var),
        ]
        for w in self.lock_widgets:
            w.pack(side="left", **pad)
        self.lock_widgets.append(self.header_entry)

        self.log_btn = ttk.Button(filef, text="▶ Avvia registrazione",
                                  command=self.toggle_logging, state="disabled")
        self.log_btn.grid(row=0, column=3, rowspan=3, sticky="ns", **pad)

        # --- Monitor
        mon = ttk.LabelFrame(self, text="Monitor seriale")
        mon.pack(fill="both", expand=True, **pad)
        self.text = tk.Text(mon, height=12, state="disabled", font=("Consolas", 10))
        sb = ttk.Scrollbar(mon, command=self.text.yview)
        self.text.configure(yscrollcommand=sb.set)
        sb.pack(side="right", fill="y")
        self.text.pack(fill="both", expand=True)
        ttk.Button(mon, text="Pulisci", command=self.clear_monitor).pack(anchor="e", **pad)

        # --- Status bar
        self.status_var = tk.StringVar(value="Non connesso")
        ttk.Label(self, textvariable=self.status_var, relief="sunken", anchor="w").pack(
            fill="x", side="bottom")

    # ------------------------------------------------------- Appunti
    def _setup_clipboard(self):
        # Tk su Windows ignora Ctrl+C/V/X con Caps Lock attivo: aggiungo le maiuscole
        self.event_add("<<Copy>>", "<Control-C>")
        self.event_add("<<Paste>>", "<Control-V>")
        self.event_add("<<Cut>>", "<Control-X>")

        # Il monitor è "disabled" (sola lettura) e di default non prende il focus:
        # senza focus Ctrl+C non arriva al widget. Lo diamo al click.
        self.text.bind("<Button-1>", lambda e: self.text.focus_set())

        self.ctx_menu = tk.Menu(self, tearoff=0)
        for w in (self.text, self.file_entry, self.header_entry):
            w.bind("<Button-3>", self._show_ctx_menu)
            w.bind("<Control-a>", lambda e: self._select_all(e.widget))
            w.bind("<Control-A>", lambda e: self._select_all(e.widget))

    def _is_editable(self, w):
        return str(w.cget("state")) == "normal" and w is not self.text

    def _show_ctx_menu(self, event):
        w = event.widget
        w.focus_set()
        ed = "normal" if self._is_editable(w) else "disabled"
        m = self.ctx_menu
        m.delete(0, "end")
        m.add_command(label="Taglia", state=ed, command=lambda: w.event_generate("<<Cut>>"))
        m.add_command(label="Copia", command=lambda: w.event_generate("<<Copy>>"))
        m.add_command(label="Incolla", state=ed, command=lambda: w.event_generate("<<Paste>>"))
        m.add_separator()
        m.add_command(label="Seleziona tutto", command=lambda: self._select_all(w))
        try:
            m.tk_popup(event.x_root, event.y_root)
        finally:
            m.grab_release()

    def _select_all(self, w):
        if isinstance(w, tk.Text):
            w.tag_add("sel", "1.0", "end-1c")
        else:
            w.select_range(0, "end")
            w.icursor("end")
        return "break"

    # ---------------------------------------------------------- Seriale
    def refresh_ports(self):
        ports = serial.tools.list_ports.comports()
        items = [f"{p.device} - {p.description}" for p in ports]
        self.port_cb["values"] = items
        # Preferisci una porta che sembri un Arduino
        pick = next((i for i in items if any(k in i.lower()
                     for k in ("arduino", "ch340", "usb serial", "cp210", "ftdi"))), None)
        if pick:
            self.port_var.set(pick)
        elif items:
            self.port_var.set(items[0])
        else:
            self.port_var.set("")

    def toggle_connection(self):
        if self.reader and self.reader.is_alive():
            self.disconnect()
        else:
            self.connect()

    def connect(self):
        sel = self.port_var.get()
        if not sel:
            messagebox.showwarning("Porta", "Nessuna porta selezionata.")
            return
        port = sel.split(" - ")[0]
        try:
            baud = int(self.baud_var.get())
        except (ValueError, tk.TclError):
            messagebox.showwarning("Baud", "Baud rate non valido.")
            return
        self.status_var.set(f"Apertura {port}…")
        self.reader = SerialReader(port, baud, self.q)
        self.reader.start()
        self.connect_btn.config(text="Disconnetti")
        self.port_cb.config(state="disabled")

    def disconnect(self):
        if self.logging:
            self.stop_logging()
        if self.reader:
            self.reader.stop()

    # --------------------------------------------------------------- CSV
    def choose_file(self):
        path = filedialog.asksaveasfilename(
            defaultextension=".csv",
            filetypes=[("CSV", "*.csv"), ("Tutti i file", "*.*")],
            initialfile=os.path.basename(self.file_var.get()))
        if path:
            self.file_var.set(path)

    def toggle_logging(self):
        if self.logging:
            self.stop_logging()
        else:
            self.start_logging()

    def start_logging(self):
        path = self.file_var.get().strip()
        if not path:
            messagebox.showwarning("File", "Specifica un file CSV.")
            return
        append = self.append_var.get() and os.path.exists(path)
        if os.path.exists(path) and not append:
            if not messagebox.askyesno("File esistente", f"{path}\nesiste già. Sovrascrivere?"):
                return
        # Congela le opzioni: header e righe devono usare le stesse colonne
        self.log_ts = self.ts_var.get()
        self.log_el = self.el_var.get()
        header = []
        if self.log_ts:
            header.append("timestamp")
        if self.log_el:
            header.append("t_s")
        header += [h.strip() for h in self.header_var.get().split(",") if h.strip()]

        # In modalità "accoda" verifica che l'intestazione esistente sia la stessa
        if append:
            try:
                with open(path, newline="", encoding="utf-8") as f:
                    old_header = next(csv.reader(f, delimiter=CSV_DELIMITER), [])
            except OSError:
                old_header = []
            if old_header != header:
                if not messagebox.askyesno(
                        "Colonne diverse",
                        "L'intestazione del file esistente è diversa dalle colonne attuali:\n\n"
                        f"file:   {CSV_DELIMITER.join(old_header)}\n"
                        f"attuali: {CSV_DELIMITER.join(header)}\n\n"
                        "Le colonne risulterebbero disallineate. Continuare comunque?"):
                    return

        try:
            self.csv_file = open(path, "a" if append else "w", newline="", encoding="utf-8")
        except OSError as e:
            messagebox.showerror("Errore file", str(e))
            return

        self.csv_writer = csv.writer(self.csv_file, delimiter=CSV_DELIMITER)
        if not append and header:
            self.csv_writer.writerow(header)

        self.rows_written = 0
        self.t0 = time.monotonic()
        self.logging = True
        for w in self.lock_widgets:
            # "readonly" (non "disabled") sui campi testo: resta possibile selezionare e copiare
            w.config(state="readonly" if isinstance(w, ttk.Entry) else "disabled")
        self.log_btn.config(text="■ Ferma registrazione")
        self.status_var.set(f"Registrazione su {os.path.basename(path)}")

    def stop_logging(self):
        self.logging = False
        if self.csv_file:
            try:
                self.csv_file.close()
            except OSError:
                pass
        self.csv_file = None
        self.csv_writer = None
        for w in self.lock_widgets:
            w.config(state="normal")
        self.log_btn.config(text="▶ Avvia registrazione")
        self.status_var.set(f"Registrazione fermata - {self.rows_written} righe salvate")

    def write_row(self, line):
        values = [v.strip() for v in line.split(INPUT_SEPARATOR)]
        row = []
        if self.log_ts:
            row.append(datetime.now().isoformat(sep=" ", timespec="milliseconds"))
        if self.log_el:
            row.append(f"{time.monotonic() - self.t0:.3f}")
        row += values
        self.csv_writer.writerow(row)
        self.rows_written += 1
        if self.rows_written % FLUSH_EVERY == 0:
            self.csv_file.flush()
        self.status_var.set(f"Registrazione… {self.rows_written} righe")

    # ------------------------------------------------------------ Coda
    def process_queue(self):
        try:
            while True:
                kind, payload = self.q.get_nowait()
                if kind == "data":
                    self.append_monitor(payload)
                    if self.logging:
                        try:
                            self.write_row(payload)
                        except OSError as e:
                            self.stop_logging()
                            messagebox.showerror("Errore scrittura", str(e))
                elif kind == "status":
                    self.status_var.set(payload)
                    self.log_btn.config(state="normal")
                elif kind == "error":
                    self.status_var.set(payload)
                    messagebox.showerror("Errore", payload)
                elif kind == "closed":
                    if self.logging:
                        self.stop_logging()
                    self.connect_btn.config(text="Connetti")
                    self.port_cb.config(state="readonly")
                    self.log_btn.config(state="disabled")
                    self.status_var.set("Disconnesso")
        except queue.Empty:
            pass
        self.after(50, self.process_queue)

    def append_monitor(self, line):
        self.text.config(state="normal")
        self.text.insert("end", line + "\n")
        n = int(self.text.index("end-1c").split(".")[0])
        if n > MAX_LOG_LINES:
            self.text.delete("1.0", f"{n - MAX_LOG_LINES}.0")
        self.text.see("end")
        self.text.config(state="disabled")

    def clear_monitor(self):
        self.text.config(state="normal")
        self.text.delete("1.0", "end")
        self.text.config(state="disabled")

    def on_close(self):
        self.disconnect()
        if self.csv_file:
            self.stop_logging()
        self.after(200, self.destroy)


if __name__ == "__main__":
    App().mainloop()
