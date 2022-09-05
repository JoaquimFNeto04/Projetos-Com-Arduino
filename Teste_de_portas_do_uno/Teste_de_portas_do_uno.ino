void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {

  int a = digitalRead (2);
  int b = digitalRead (3);
  int c = digitalRead (4);
  int d = digitalRead (5);
  int e = digitalRead (6);
  int f = digitalRead (7);
  int g = digitalRead (8);
  int h = digitalRead (9);
  int i = digitalRead (10);
  int j = digitalRead (11);
  int k = digitalRead (12);
  int l = digitalRead (13);
  
  int m = digitalRead (A0);
  int n = digitalRead (A1);
  int o = digitalRead (A2);
  int p = digitalRead (A3);
  int q = digitalRead (A4);
  int r = digitalRead (A5);

  Serial.println ();

  Serial.print ("PORTA 2 = ");
  Serial.println (a);

  Serial.print ("PORTA 3 = ");
  Serial.println (b);

  Serial.print ("PORTA 4 = ");
  Serial.println (c);

  Serial.print ("PORTA 5 = ");
  Serial.println (d);

  Serial.print ("PORTA 6 = ");
  Serial.println (e);

  Serial.print ("PORTA 7 = ");
  Serial.println (f);

  Serial.print ("PORTA 8 = ");
  Serial.println (g);

  Serial.print ("PORTA 9 = ");
  Serial.println (h);

  Serial.print ("PORTA 10 = ");
  Serial.println (i);

  Serial.print ("PORTA 11 = ");
  Serial.println (j);

  Serial.print ("PORTA 12 = ");
  Serial.println (k);

  Serial.print ("PORTA 13 = ");
  Serial.println (l);

  Serial.print ("PORTA A0 = ");
  Serial.println (m);

  Serial.print ("PORTA A1 = ");
  Serial.println (n);

  Serial.print ("PORTA A2 = ");
  Serial.println (o);

  Serial.print ("PORTA A3 = ");
  Serial.println (p);

  Serial.print ("PORTA A4 = ");
  Serial.println (q);

  Serial.print ("PORTA A5 = ");
  Serial.println (r);

  delay(2000);

}
