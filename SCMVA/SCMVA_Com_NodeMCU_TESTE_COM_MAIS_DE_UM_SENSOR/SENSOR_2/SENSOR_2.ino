#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8d57866049bd4c708e1e4abda87a0b73";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NCLOUD";
char pass[] = "";

//variaveis do leitor 1
float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para contagem
//fim variaveis do leitor

const byte interruptPin = 5; // Pino que Sera conectado o medidor de fluxo 1
const byte interruptPin2 = 13; // Pino que Sera conectado o medidor de fluxo 2

int a1 = 0;
int c = 0;
float GastoemL = 0;
float vazaototal = 0;

//variaveis do leitor 2
float vazao2; //Variável para armazenar o valor em L/min
float media2 = 0; //Variável para tirar a média a cada 1 minuto
int contaPulso2; //Variável para a quantidade de pulsos
int i2 = 0; //Variável para contagem
//fim variaveis do leitor 2

void setup()
{
  // Debug console
  Serial.begin(9600); //Inicia a serial com um baud rate de 9600

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT);
  pinMode(13, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incpulso, RISING); //Configura o pino D1(Interrupção 0) para trabalhar como interrupção
  //attachInterrupt(digitalPinToInterrupt(interruptPin2), incpulso2, RISING); //Configura o pino D2(Interrupção 0) para trabalhar como interrupção
  Serial.println("\n\nInicio\n\n"); //Imprime Inicio na serial

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
}

void loop() {

  Serial.print("TOTAL DE LOOP E = ");
  Serial.println(c);
  c++;
  //testedeconexao();
  Blynk.run();
  leitura1();
  //leitura2();

  Serial.println("");

}

void testedeconexao() {
  WidgetLED conexao(V4);
  conexao.on();
  delay(200);
  conexao.off();
  delay(200);
}

void leitura1 () {
  /*
    int Reset;
    Reset = digitalRead (4);
    if (Reset == 0) {
      int nreset = 10;
      while (nreset <= 10) {
        Reset = digitalRead (4);
        if (Reset != 0){
         nreset = 11;
        }

        Serial.println ("DESEJA CONTINUAR ?");
        Serial.println (nreset);
        nreset--;
        delay(1000);
      }
      if (nreset == 0) {
        GastoemL = 0;
        vazao = 0;
        media = 0;
        i = 0;
        Blynk.virtualWrite (V0, GastoemL);// Total Gasto No Grafico
        Blynk.virtualWrite (V1, GastoemL);// Total Gasto No Display
        Serial.println ("Sistema apagado com Sucesso!");
        Serial.println ("Favor Soltar o Reset Para Continuar.");
        delay(2000);
      }
    }*/

  //else {


  contaPulso = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção

  vazao = contaPulso / 5.5; //Converte para L/min
  media = media + vazao; //Soma a vazão para o calculo da media
  i++;
  Serial.print("A VAZAO E = ");
  Serial.println(vazao); //Imprime na serial o valor da vazão
  Blynk.virtualWrite (V0, vazao);
  Blynk.virtualWrite (V1, vazao);
  Blynk.virtualWrite (V2, vazao);
  /* Serial.print(" L/min - "); //Imprime L/min
  Serial.print(i); //Imprime a contagem i (segundos)
  Serial.println("s"); //Imprime s indicando que está em segundos */

  vazaototal = vazaototal + vazao;
  Serial.print("A VAZAO TOTAL E = ");
  Serial.println(vazaototal);
  Blynk.virtualWrite (V9, vazaototal);
  Blynk.virtualWrite (V10, vazaototal);
  Blynk.virtualWrite (V11, vazaototal);

  if (i == 60)
  {
    media = media / 60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Blynk.virtualWrite (V3, media);
    Blynk.virtualWrite (V4, media);
    Blynk.virtualWrite (V5, media);
    Serial.println(" L/min - "); //Imprime L/min
    GastoemL = GastoemL + media;
    Serial.print("GASTO EM L E = ");
    Serial.println(GastoemL);
    Blynk.virtualWrite (V6, GastoemL);// Total Gasto No Grafico
    Blynk.virtualWrite (V7, GastoemL);// Total Gasto No Display
    Blynk.virtualWrite (V8, GastoemL);// Total Gasto No Display
    media = 0; //Zera a variável media para uma nova contagem
    i = 0; //Zera a variável i para uma nova contagem
    //Blynk.virtualWrite (V0, media);
    //Serial.println("\n\nInicio 1\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }

  /*a1++;

    if (a1 == 2629800000) {
    a == 0;
    a1 == 0;
    }*/

  //}
}

/*void leitura2() {

  contaPulso2 = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção

  vazao2 = contaPulso2 / 5.5; //Converte para L/min
  media2 = media2 + vazao2; //Soma a vazão para o calculo da media
  i2++;
  int MediaAtual2 = media2 / i2;
  //Blynk.virtualWrite (V3, MediaAtual2);

  Serial.print(vazao2); //Imprime na serial o valor da vazão
  //Blynk.virtualWrite (V3, vazao2);
  Serial.print(" L/min 2 - "); //Imprime L/min
  Serial.print(i2); //Imprime a contagem i (segundos)
  Serial.println("s"); //Imprime s indicando que está em segundos

  if (i2 == 60)
  {
    media2 = media2 / 60; //Tira a media dividindo por 60
    Serial.print("\nMedia2 por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media2); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    media2 = 0; //Zera a variável media para uma nova contagem
    i2 = 0; //Zera a variável i para uma nova contagem
    //Blynk.virtualWrite (V2, media2);
    Serial.println("\n\nInicio 2\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }

  }
*/
void incpulso ()
{
  contaPulso++; //Incrementa a variável de contagem dos pulsos
}
/*
  void incpulso2 ()
  {
  contaPulso2++; //Incrementa a variável de contagem dos pulsos
  }*/
