

void setup() {

pinMode (2,INPUT_PULLUP);
pinMode (3,INPUT_PULLUP);
pinMode (4,INPUT_PULLUP);
pinMode (5,INPUT_PULLUP);
pinMode (6,INPUT_PULLUP);
pinMode (7,INPUT_PULLUP);
pinMode (8,INPUT_PULLUP);
pinMode (9,INPUT_PULLUP);

Serial.begin(9600);


}

void loop() {

int a = digitalRead(2);
int b = digitalRead(3);
int c = digitalRead(4);
int d = digitalRead(5);
int e = digitalRead(6);
int f = digitalRead(7);
int g = digitalRead(8);
int h = digitalRead(9);

Serial.print ("Porta 2 = ");
Serial.println (a);

Serial.print ("Porta 3 = ");
Serial.println (b);

Serial.print ("Porta 4 = ");
Serial.println (c);

Serial.print ("Porta 5 = ");
Serial.println (d);

Serial.print ("Porta 6 = ");
Serial.println (e);

Serial.print ("Porta 7 = ");
Serial.println (f);

Serial.print ("Porta 8 = ");
Serial.println (g);

Serial.print ("Porta 9 = ");
Serial.println (h);

Serial.println ("");
Serial.println ("");

delay(2000);
}
