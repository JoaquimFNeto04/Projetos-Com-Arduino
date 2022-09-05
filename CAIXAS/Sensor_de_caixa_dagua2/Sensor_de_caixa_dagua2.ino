#define sensor1 A6
#define sensor2 A7
int val1;
int val2;
void setup() {
  
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  
  Serial.begin (9600);
  Serial.print ("Leitor de Caixa d'agua");
  Serial.println ("Carregando Aguarde.");
  delay(500);
}

void loop() {
  
  val1 = analogRead(sensor1);
  val2 = analogRead(sensor2);

  Serial.print ("val1 = ");
  Serial.print (val1);
  Serial.print (" e o val2 = ");
  Serial.println (val2);
  delay(1000);
}
