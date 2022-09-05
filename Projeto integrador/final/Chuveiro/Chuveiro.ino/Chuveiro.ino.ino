#include <Ultrasonic.h>


#define TRIGGER_PIN  12
#define ECHO_PIN     13

int x = 0;
int valvula = 3;
int fluxo = 2;
float vazao; //Variável para armazenar o valor em L/min
float media=0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i=0; //Variável para contagem

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
  {
  Serial.begin(9600);
  pinMode(valvula, OUTPUT);
  pinMode(fluxo, INPUT);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) para trabalhar como interrupção
  }

void loop()
  {
  
  delay(1000);  
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  
  if (cmMsec <= 120){
   digitalWrite(valvula, LOW);
   Serial.println("Chuveiro Ligado.");
  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção

  vazao = contaPulso / 5.5; //Converte para L/min
  media=media+vazao; //Soma a vazão para o calculo da media
  i++;

  if (i == 60){
   
    x++;
    i=0;
    media = media/60; //Tira a media dividindo por 60
    
  Serial.print("Você está com o Chuveiro Ligado a: ");
  Serial.print(x);
  Serial.println(" Minutos");
  Serial.print("E você Gastou: ");
  Serial.print(media);
  Serial.println(" L/min\n");
  media = 0; //Zera a variável media para uma nova contagem   
   } 
  } 
   else if (cmMsec >= 120) {
   digitalWrite(valvula, HIGH);
   Serial.println("Chuveiro Desligado.");
 }
}
void incpulso ()
{ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
} 
