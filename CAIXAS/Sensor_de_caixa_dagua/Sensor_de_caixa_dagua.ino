#define bomba 2
#define sensor1 A6
#define sensor2 A7
int val1;
int val2;
void setup() {
  
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (bomba, OUTPUT);
  
  Serial.begin (9600);
  Serial.print ("Leitor de Caixa d'agua");
  Serial.println ("Carregando Aguarde.");
  digitalWrite(bomba, LOW);
  delay(500);
}

void loop() {
  
  val1 = analogRead(sensor1);
  val2 = analogRead(sensor2);

  //Inicio do Defeito
    
    
  Serial.print ("val1 = ");
  Serial.print (val1);
  Serial.print (" e o val2 = ");
  Serial.println (val2);
    
    if((val1 < 511)and(val2 > 511)){
     Serial.println ("Algum dos Sensores esta com defeito");
     Serial.println ("Entre em Contato com suporte pelo telefone (83) 3033-3391");
     digitalWrite(bomba, LOW);  
    }
  //Fim do Defeito  

  //Inicio do vazio
    if(val2 <= 511){
     Serial.println ("A caixa esta vazia e a bomba sera ligada.");
     digitalWrite(bomba, HIGH);
     }    
  //Fim do vazio

    //Inicio do medio
    if((val2 < 511)and(val1 > 511)){
     Serial.println ("A caixa esta na metade");
    }       
   //Fim do medio

   //Inicio do cheio
    if(val1 < 511){
     Serial.println ("A caixa esta cheia e a bomba sera desligada");
     digitalWrite(bomba, LOW);
    }
   //Fim do cheio
   delay(1000);
}
