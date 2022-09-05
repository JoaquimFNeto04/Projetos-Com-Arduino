#define sensor 2
#define bomba 3

void setup() {

  pinMode(sensor, INPUT_PULLUP);
  pinMode(bomba, OUTPUT);
  digitalWrite(bomba, HIGH);
  Serial.begin(9600);
}

void loop() {

  leitura();


}

void leitura () {

  int statussensor = digitalRead(sensor);

  Serial.println ("O STATUS DO SENSOR E");
  Serial.println (statussensor);
  if (statussensor == 0) {
    bombadesligada();
  }

  else if (statussensor == 1) {
    bombaligada();
  }

}

void bombadesligada () {

  delay(10000);
  digitalWrite(bomba, HIGH);
  Serial.println("A BOMBA ESTA DESLIGADA.");

}

void bombaligada () {

  delay(10000);
  digitalWrite(bomba, LOW);
  Serial.println("A BOMBA ESTA LIGADA.");

}

