// joaquim testando bluetooth.

int led = 5;

boolean statuslampada = true; 

void setup() {
  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
}

void loop() {
 char comando = Serial.read();

 if (comando = 's'){
  if(statuslampada){
    Serial.println("1off");
  }
  else {
    Serial.println("1on");
  }
  delay(250);
 }


 if (comando == 'a'){
  if(statuslampada) {
    digitalWrite(led, LOW);
    statuslampada = false;
    Serial.println("1on");
  }
  else{
    digitalWrite(led, HIGH);
    statuslampada = true;
    Serial.println("1on");    
  }

 }
}
