#include <SoftwareSerial.h>//
SoftwareSerial mySerial(10, 3); // 10-RX, 3-TX
float vazao; //Variável para armazenar o valor em L/min
float media=0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i=0; //Variável para contagem
int led = 4;
int rele = 8;

void setup()
{ 
  Serial.begin(9600); //Inicia a serial com um baud rate de 9600
  mySerial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(led, OUTPUT);//Pino digital saÃ­da do Arduino(4-ch1);
  pinMode(rele, OUTPUT);//Pino digital saÃ­da do Arduino(5-ch2);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) para trabalhar como interrupção
  Serial.println("\n\nInicio\n\n"); //Imprime Inicio na serial
   
    //Envia o valor inicial zero do contador para o Android  
  Serial.write(201);   
  Serial.write(highByte(2));  
  Serial.write(lowByte(2));  
  
} 


void loop ()
{

 char caracter = mySerial.read();
 //--------------------------------led---------------------
 if(caracter == 'A')
{
 digitalWrite(led,HIGH);
}

if(caracter == 'B')
{
 digitalWrite(led,LOW);
}
//---------------------------------led----------------------
 //--------------------------------rele---------------------
 if(caracter == 'C')
{
 digitalWrite(rele,HIGH);
}

if(caracter == 'D')
{
 digitalWrite(rele,LOW);
}
//---------------------------------rele----------------------

  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção
  
  vazao = contaPulso / 5.5; //Converte para L/min
  media=media+vazao; //Soma a vazão para o calculo da media
  i++;
  
  Serial.print(vazao); //Imprime na serial o valor da vazão
  Serial.print(" L/min - "); //Imprime L/min
  Serial.print(i); //Imprime a contagem i (segundos)
  Serial.println("s"); //Imprime s indicando que está em segundos
  
  if(i==60)
  {
    media = media/60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    media = 0; //Zera a variável media para uma nova contagem
    i=0; //Zera a variável i para uma nova contagem
    Serial.println("\n\nInicio\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }

   //Envia as informacoes do potenciometro para o Android  
  int valor_fluxo = digitalRead(2);  
  Serial.write(202);  
  Serial.write(valor_fluxo);  
  Serial.write(valor_fluxo);  
  delay(50);

}
 
 
void incpulso ()
{ 
  contaPulso++; //Incrementa a variável de contagem dos pulsos
} 
