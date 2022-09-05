#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
     char auth[] = "d579a815ae604ecca4de4394afca8867"; // LEITOR 1
//   char auth[] = "0ee04728d14d4f6dac5ad11b6d90e4d7"; // LEITOR 2

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "casa";
char pass[] = "marcos10";

//variaveis do leitor
float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para tirar a média a cada 1 minuto
double GastoemL = 0; //Variável para tirar a média a cada 1 minuto
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para contagem
//fim variaveis do leitor

//variaveis do leitor 2
float vazao2; //Variável para armazenar o valor em L/min
float media2 = 0; //Variável para tirar a média a cada 1 minuto
double GastoemL2 = 0; //Variável para tirar a média a cada 1 minuto
int contaPulso2; //Variável para a quantidade de pulsos
int i2 = 0; //Variável para contagem
//fim variaveis do leitor 2

const byte interruptPin = D2; // Pino que Sera conectado o medidor de fluxo 1
const byte interruptPin2 = D6; // Pino que Sera conectado o medidor de fluxo 2

void setup()
{
  // Debug console
  Serial.begin(9600); //Inicia a serial com um baud rate de 9600

  pinMode(4, INPUT_PULLUP);
  pinMode(D2, INPUT);
  pinMode(D6, INPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin), incpulso, RISING); //Configura o pino D1(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(interruptPin2), incpulso2, RISING); //Configura o pino D2(Interrupção 0) para trabalhar como interrupção
  Serial.println("\n\nInicio\n\n"); //Imprime Inicio na serial

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
}

void loop() {

  testedeconexao();
  Blynk.run();
  leitura1();
  leitura2();
}


void testedeconexao() {
  WidgetLED conexao(V0);
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
  Serial.print(" VAZAO = "); //Imprime L/min
  Serial.println(vazao); //Imprime a contagem i (segundos)
  Serial.println(i); //Imprime s indicando que está em segundos
  i++;

  
  Serial.print("\nTOTAL GASTOS = "); //Imprime a frase Media por minuto =
  Serial.print(GastoemL); //Imprime o valor da media
  Serial.println(" L/min - "); //Imprime L/min
  Blynk.virtualWrite (V1, GastoemL);// Total Gasto No Grafico
  Blynk.virtualWrite (V2, GastoemL);// Total Gasto No Display
  Blynk.virtualWrite (V3, GastoemL);// Total Gasto No Display 2

  //Serial.print(vazao); //Imprime na serial o valor da vazão
  // Blynk.virtualWrite (V2, vazao);
  // Serial.print(" L/min - "); //Imprime L/min
  //Serial.print(i); //Imprime a contagem i (segundos)
  //Serial.println("s"); //Imprime s indicando que está em segundos

  if (i == 60)
  {
    media = media / 60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    GastoemL = GastoemL + media;
    media = 0; //Zera a variável media para uma nova contagem
    i = 0; //Zera a variável i para uma nova contagem
    //Blynk.virtualWrite (V4, media);
    Serial.println("\n\nInicio 1\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }
}

void leitura2() {

  contaPulso2 = 0;   //Zera a variável para contar os giros por segundos
  sei();      //Habilita interrupção
  delay (1000); //Aguarda 1 segundo
  cli();      //Desabilita interrupção

  vazao2 = contaPulso2 / 5.5; //Converte para L/min
  media2 = media2 + vazao2; //Soma a vazão para o calculo da media
  Serial.print(" VAZAO 2 = "); //Imprime L/min
  Serial.println(vazao2); //Imprime a contagem i (segundos)
  Serial.println(i2); //Imprime s indicando que está em segundos
  i2++;

  
  Serial.print("\nTOTAL GASTOS 2 = "); //Imprime a frase Media por minuto =
  Serial.print(GastoemL2); //Imprime o valor da media
  Serial.println(" L/min - "); //Imprime L/min
  Blynk.virtualWrite (V4, GastoemL2);// Total Gasto No Grafico
  Blynk.virtualWrite (V5, GastoemL2);// Total Gasto No Display
  Blynk.virtualWrite (V6, GastoemL2);// Total Gasto No Display 2

  //Serial.print(vazao); //Imprime na serial o valor da vazão
  // Blynk.virtualWrite (V2, vazao);
  // Serial.print(" L/min - "); //Imprime L/min
  //Serial.print(i); //Imprime a contagem i (segundos)
  //Serial.println("s"); //Imprime s indicando que está em segundos

  if (i2 == 60)
  {
    media2 = media2 / 60; //Tira a media dividindo por 60
    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
    Serial.print(media); //Imprime o valor da media
    Serial.println(" L/min - "); //Imprime L/min
    GastoemL2 = GastoemL2 + media2;
    media2 = 0; //Zera a variável media para uma nova contagem
    i2 = 0; //Zera a variável i para uma nova contagem
    //Blynk.virtualWrite (V4, media);
    Serial.println("\n\nInicio 1\n\n"); //Imprime Inicio indicando que a contagem iniciou
  }
  }

void incpulso ()
{
  contaPulso++; //Incrementa a variável de contagem dos pulsos
}

void incpulso2 ()
{
  contaPulso2++; //Incrementa a variável de contagem dos pulsos
}
