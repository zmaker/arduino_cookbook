import tkinter as tk
from pystray import MenuItem as item
import pystray
from PIL import Image, ImageTk

from tkinter import Frame
from tkinter import Button
from tkinter import ttk

import threading
import time

import serial.tools.list_ports
import pyfirmata

import openpyxl

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Arduino XLS")
        self.geometry("300x200")
        self.protocol('WM_DELETE_WINDOW', self.hide_window)
        
        self.CONNECTED = False
        
        ports = []
        for port in serial.tools.list_ports.comports():
            print(port)
            ports.append(port.device)
        
        frame = Frame(self)
        frame.pack()
        self.combo = ttk.Combobox(frame, values=ports)
        self.combo.set("Scegli la seriale")
        self.combo.pack(padx=5, pady=5)
        
        button = Button(frame, text="Connetti", command=self.connectArduino)
        button.pack(pady=5)
        
        t = threading.Thread(target=self.controllafile)
        t.setDaemon(True)
        t.start()
        
    
    def quit_window(self):
        self.LOOP = False
        icon.stop()
        self.destroy()
    
    def show_window(self):
        icon.stop()
        self.after(0, self.deiconify())
    
    def hide_window(self):
        self.withdraw()
        self.image = Image.open("favicon.ico")
        menu = (item('Quit', self.quit_window), item('Show', self.show_window))
        icon = pystray.Icon("name", self.image, "Arduino Xls", menu)
        icon.run()

    def connectArduino(self):
        self.board = pyfirmata.Arduino(self.combo.get())
        self.board.digital[13].write(1)
        time.sleep(1)
        self.board.digital[13].write(0)
        time.sleep(1)
        self.CONNECTED = True

    
    def controllafile(self):
        self.LOOP = True
        while (self.LOOP):
            wb = openpyxl.load_workbook("arduino.xlsx")
            ws = wb.active
            if (self.CONNECTED):
                for pin in range(2,14):
                    cx = ws.cell(column=2, row=pin)
                    pin_value = int(cx.value)
                    self.board.digital[pin].write(pin_value)
                    
            wb.close()
            time.sleep(1)

if __name__ == "__main__":
    app = App()
    app.mainloop()