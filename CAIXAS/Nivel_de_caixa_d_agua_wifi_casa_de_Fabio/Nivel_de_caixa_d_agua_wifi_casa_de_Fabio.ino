// fabio

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "194d10c31dda456f9db2100caf77c647";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Neto";
char pass[] = "12345678";

#define caixa_boia_1 D2
#define caixa_boia_2 D3
#define caixa_boia_3 D4

#define NivelCaixa   V2
int controle = 0;

void setup() {

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(caixa_boia_1, INPUT_PULLUP);
  pinMode(caixa_boia_2, INPUT_PULLUP);
  pinMode(caixa_boia_3, INPUT_PULLUP);

  WidgetLCD Display(V1);
  Display.clear();
  Display.print(1, 0, "O SISTEMA ESTA");
  Display.print (4, 1, "CARREGANDO");
  delay(2000);

}

void loop() {

  WidgetLCD Display(V1);
  Blynk.run();

  LeituraCaixa();
  testedeconexao();
  Serial.print ("CONTROLE = ");
  Serial.println (controle);

  if (controle == 5) {
    Blynk.notify(" A CAIXA ESTA COM NIVEL BAIXO");
    Blynk.email("superboxmf@hotmail.com", "CAIXA DE AGUA DE FABIO", "A CAIXA D'AGUA DE FABIO ESTA NO NIVEL BAIXO FAVOR PROVIDENCIAR O ABSTECIMENTO");
   // Blynk.email("automacaocasadefabio@gmail.com", "CAIXA DE AGUA DE FABIO", "A CAIXA D'AGUA DE FABIO ESTA NO NIVEL BAIXO FAVOR PROVIDENCIAR O ABSTECIMENTO");
  }
  if ((controle >= 51) and (controle % 60 == 0) or (controle == 54)) {
    Blynk.notify(" A CAIXA ESTA COM NIVEL CRITICO");
    Blynk.email("superboxmf@hotmail.com", "CAIXA DE AGUA DE FABIO", "A CAIXA D'AGUA DE FABIO ESTA NO NIVEL CRITICO FAVOR PROVIDENCIAR O ABSTECIMENTO");
    //Blynk.email("automacaocasadefabio@gmail.com", "CAIXA DE AGUA DE FABIO", "A CAIXA D'AGUA DE FABIO ESTA NO NIVEL CRITICO FAVOR PROVIDENCIAR O ABSTECIMENTO");
  }

}

void testedeconexao() {
  WidgetLED conexao(V0);
  conexao.on();
  delay(200);
  conexao.off();
  delay(200);
}

void LeituraCaixa() {

  WidgetLCD Display(V1);
  int nivel = 0;

  testedeconexao();

  if (digitalRead(caixa_boia_1)) nivel++;
  if (digitalRead(caixa_boia_2)) nivel++;
  if (digitalRead(caixa_boia_3)) nivel++;

  Serial.print (" NIVEL = ");
  Serial.println (nivel);

  if (nivel == 0) {

    testedeconexao();

    Blynk.setProperty(NivelCaixa, "color", "#ff0000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O NIVEL  CRITICO");


    if (controle >= 51) {
      controle++;
    }

    else if (controle <= 51) {
      controle = 51;
    }

  }

  if (nivel == 1) {

    testedeconexao();

    Blynk.setProperty(NivelCaixa, "color", "#ff0000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  BAIXO ");

    controle++;

    if (controle == 50) {
      controle = 0;
    }

    delay (1000);
  }

  if (nivel == 2) {

    testedeconexao();

    controle = 0;

    Blynk.setProperty(NivelCaixa, "color", "#FFA500");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  MEDIO ");
    delay (1000);


  }

  if (nivel == 3) {

    testedeconexao();

    controle = 0;

    Blynk.setProperty(NivelCaixa, "color", "#008000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  CHEIO ");

    delay (1000);
  }
  Blynk.virtualWrite(NivelCaixa, nivel);
}
