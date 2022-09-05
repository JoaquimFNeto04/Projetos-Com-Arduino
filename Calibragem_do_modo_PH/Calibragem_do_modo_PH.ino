int i = 0; //valor de tempo para fazer uma media
int j = 10;
int carregando = 0;
int phresultado = 0;
int ph = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println ("MANTENHA O SENSOR NO LIQUIDO E AGUARDE.");
  Serial.print ("CARREGANDO ");
}
// the loop routine runs over and over showing the voltage on A0
void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);


  if (carregando <= 5 ) {
    Serial.print (".");
    carregando++;
    delay(1000);
  }

  else if ((carregando >= 6 ) and (carregando <= 12 )) {
    Serial.print (".");
    carregando++;
    delay(100);
  }

  else if (carregando == 13 ) {
    Serial.println (" ");
    Serial.println ("LEITURAS INICIADAS. ");
    Serial.println (" ");
    carregando++;
    delay(300);
  }

  else if (carregando > 13 ) {

    //Serial.print ("Voltage ");
    //Serial.println(voltage);

    ph = voltage * 2.8;
    phresultado = map(ph,0,14,14,0);
    j++;
    
    if (j == 11) {
      Serial.print ("O RESULTADO DO PH e: ");
      Serial.println (phresultado);
      Serial.println (" ");
      j = 0;
    }
  }
  delay(500);
}
