#include <NewPing.h>

float vazao; //Variável para armazenar o valor em L/min
float media=0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i=0; //Variável para contagem
int led;
int rele = 3;
void setup(){

  Serial.begin(9600); //Inicia a serial com um baud rate de 9600
  pinMode(2, INPUT);
  pinMode(led, OUTPUT);//Pino digital saÃ­da do Arduino(4-ch1);
  pinMode(rele, OUTPUT);//Pino digital saÃ­da do Arduino(5-ch2);
  digitalWrite(rele, LOW);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) para trabalhar como interrupção
  Serial.println("\n\nInicio\n\n"); //Imprime Inicio na serial
   
 
}

void loop (){


  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção
  
  vazao = contaPulso / 5.5; //Converte para L/min
  media=media+vazao; //Soma a vazão para o calculo da media
  i++;

  if(i == 60){
    mediaporminuto = media/60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    media = 0; //Zera a variável media para uma nova contagem
    i=0; //Zera a variável i para uma nova contagem
  }
}

void incpulso ()
{ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
}

