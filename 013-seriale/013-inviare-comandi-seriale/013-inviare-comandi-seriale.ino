#include <Servo.h> // richiama la libreria di gestione dei servomotori

Servo servobase; // crea i servoggetti per ogni servo del braccio meccanico.

Servo servobraccio;

Servo servoavambraccio;

Servo servopolso;

Servo servogirapolso;

Servo servomano;

int statogiu = 0; // variabile di memorizzazione dello stato del pulsante giu

int statosu = 0; // Variabile di memorizzazione dello stato del pulsante su

int statosele = 0; // variabile di memorizzazione dello stato del pulsante "selezione"

int indix = 0; // indice utilizzato in diversi cicli di for

long tempoinizio = 0; // memorizza il momento dela selezione 6 (selta sequenza programmata)

long tempoattuale = 0; // memorizza il momento di verifica del tempo trascorso dalla selezione 6

int mossa = 0; // numero di mossa della sequenza programmata

int mossainiziale = 0; // numero della mossa di partenza, in tabella tabprog

int tempo = 0; // tempo da impegnare per lo spostamento di 1 grado

int movimento = 1; // movimento di un grado sul servomotore selezionato. Puo' essere positivo (1)

// negativo (-1) a seconda che i gradi da raggiungere siano superiori o inferiori ai gradi correnti

// Movement of 1 degree on the selected servo motor. Can 'be positive (1) or negative (-1) depending

// if degrees to be achieved are above or below the current degrees

int sele = 0; // selezione del servomotore da 0 a 5, in sequenza: base, braccio, avambraccio,

// polso, girapolso, mano – servomotor selected and working (from 0 to 5)

int selezione = 0; // selezione operata tramite pulsanti

char descservo [7][12] = // descrizione dei servomotori _ servomotor description

{

{"base "}, // base

{"braccio "}, // arm

{"avambraccio"}, // forearm

{"polso "}, // wrist

{"girapolso "}, // wrist turn

{"mano "}, // hand

{"seq.program"}, // programmed sequence

};

// Arduino: braccio meccanico – robotic arm

// Servo motor, mechanical hand, 1602 lcd,

int tabgradi [8]; // memorizzazione dei gradi di ognuno dei servomotori – current degrees for each

int tabprog [151] = // tabella di memorizzazione della sequenza di mosse programmate (max 50 mosse).

// ogni mossa prevede tre parametri: il numero del servomotre (da 0 a 5), i gradi

// che deve raggiungere ed il tempo per compiere il movimento di un grado. il servomotore "99"

// storage array for programmed moves (max 50).

// Each move requires three parameters: the servo number (0 to 5), egrees that must reached and

// time for a one degree movement.

// Servo "99" closes the series of planned moves

//servo, gradi, velocita’ (tempo per il movimento di un grado)

// servo, degrees, speed (time for one degree movement)

{

1, 56, 30, // mossa 0 move #0

0, 90, 40, // mossa 1 move #1

4, 51, 20, // mossa 2 ...

2, 76, 20, // mossa 3

3, 30, 20, // mossa 4

5, 53, 30, // mossa 5

2, 43, 20, // mossa 6

0, 45, 40, // mossa 7

5, 23, 30, // mossa 8

99, 0, 0, // mossa 9

0, 0, 0, // mossa 10

0, 0, 0, // mossa 11

0, 0, 0, // mossa 12

0, 0, 0, // mossa 13

0, 0, 0, // mossa 14

0, 0, 0, // mossa 15

0, 0, 0, // mossa 16

0, 0, 0, // mossa 17

0, 0, 0, // mossa 18

0, 0, 0, // mossa 19

0, 0, 0, // mossa 20

0, 0, 0, // mossa 21

0, 0, 0, // mossa 22

0, 0, 0, // mossa 23

0, 0, 0, // mossa 24

0, 0, 0, // mossa 24

0, 0, 0, // mossa 26

0, 0, 0, // mossa 27

0, 0, 0, // mossa 28

0, 0, 0, // mossa 29

0, 0, 0, // mossa 30

0, 0, 0, // mossa 31

0, 0, 0, // mossa 32

0, 0, 0, // mossa 33

0, 0, 0, // mossa 34

0, 0, 0, // mossa 35

0, 0, 0, // mossa 36

0, 0, 0, // mossa 37

0, 0, 0, // mossa 38

0, 0, 0, // mossa 39

0, 0, 0, // mossa 40

0, 0, 0, // mossa 41

0, 0, 0, // mossa 42

0, 0, 0, // mossa 43

// le seguenti mosse sono utilizzate per fare assumere al braccio la posizione iniziale

// The following moves are used to set arm in starting position

5, 0, 20, // mossa 44

4, 0, 20, // mossa 45

3, 0, 20, // mossa 46

2, 0, 20, // mossa 47

1, 56, 30, // mossa 48

0, 90, 40, // mossa 49

};

void sequenzaprogrammata (void)

{

for (mossa = mossainiziale; mossa <= 49; mossa ++) // loop di mosse programmate

{

if (tabprog [mossa*3] == 99)

sele = tabprog [mossa * 3]; // memorizza il numero del servomotore sul quale deve agire

// Arduino: braccio meccanico – robotic arm

// Servo motor, mechanical hand, 1602 lcd,

movimento = 1;

if (tabprog [mossa * 3 + 1] < tabgradi [sele])

movimento = -1;

tempo = tabprog [mossa * 3 + 2];

while (!(tabgradi [sele] == tabprog [mossa * 3 + 1]))

{

tabgradi [sele] = tabgradi [sele] + movimento; // cambia di un grado (in + o in -, a seconda

visualizzaimpulsi ();

posizionaservo ();

}

}

selezione = 0;

}

void posizionaservo (void)

{

servobase.write (tabgradi [0]);

servobraccio.write (tabgradi [1]);

servoavambraccio.write (tabgradi [2]);

servopolso.write (tabgradi [3]);

servogirapolso.write (tabgradi [4]);

servomano.write (tabgradi [5]);

delay (tempo);

}

void acquisiscigradi (void)

{

if (tabgradi [sele] == 0)

tabgradi [sele]++;

if (tabgradi [sele] == 180)

tabgradi[sele]--;

statogiu = digitalRead (giu); // aquisisce lo stato del pulsante giu

if (statogiu == 1) // se e' stato premuto il pulsante giu

tabgradi [sele]--; // diminuisce di 1 il valore dei gradi

statosu = digitalRead (su); // aquisisce lo stato del pulsante su

if (statosu == 1) // se e' stato premuto il pulsante su

tabgradi[sele]++; // aumenta di 1 i gradi

}

void selezionaservo (void)

{

statosele = digitalRead (scelta); // aquisisce lo stato del pulsante seleziona servo

if (statosele == 1) // se e' stato premuto il pulsante di selezione

{

selezione++; // passa al servomotore successivo

if (selezione == 7)

selezione = 0;

delay (300);

}

}

void visualizzaimpulsi (void)

{

lcd.clear();

lcd.setCursor(0, 0); // posiziona il cursore all'inizio della prima riga

lcd.print (sele);

lcd.print (" - ");

lcd.print (descservo [sele]);

lcd.setCursor (0, 1);

lcd.print ("gradi = ");

// Arduino: braccio meccanico – robotic arm

// Servo motor, mechanical hand, 1602 lcd,

lcd.print (tabgradi [sele]);

lcd.print (" ");

}

void setup()

{

lcd.begin(16, 2); // inizializza il display (16 caratteri per due righe)

servobase.attach(5); // assegna il servo oggetto “servobase” alla porta 5

servobraccio.attach(6); // assegna il servo oggetto “servobarccio” alla porta 6

servoavambraccio.attach(7); // assegna il servo oggetto “servoavambraccio” alla porta 7

servopolso.attach(8); // assegna il servo oggetto “servopolso” alla porta 8

servogirapolso.attach(9); // assegna il servo oggetto “servogirapolso” alla porta 9

servomano.attach(10); // assegna il servo oggetto “servomano” alla porta 10

pinMode (giu, INPUT); // definisce il pulsante giu (pin2) come unita' di input

pinMode (su, INPUT); // definisce il pulsante su (pin3) come unita' di input

pinMode (scelta, INPUT); // definisce il pulsante scelta (pin 4) come unita' di input

tempo = 50; // esegue lentamente il movimento per raggiungere la posizione 0

posizionaservo (); // posiziona i servomotori nella posizione zero

delay (500);

mossainiziale = 44;

sequenzaprogrammata (); // Mette il braccio in posizione di inizio lavoro

mossainiziale = 0;

}

void loop ()

{

tempoinizio = millis();

selezionaservo ();

sele = selezione;

visualizzaimpulsi ();

while (selezione == 6)

{

tempoattuale = millis ();

if ((tempoattuale - tempoinizio) > 3000)

{

sequenzaprogrammata (); // esegue la sequenza programmata

mossainiziale = 44;

sequenzaprogrammata (); // Mette il braccio in posizione di inizio lavoro

mossainiziale = 0;

selezione = 0; // forza l'uscita dal loop di sequenza programmata

}

selezionaservo ();

}

acquisiscigradi ();

visualizzaimpulsi ();

posizionaservo ();

}
