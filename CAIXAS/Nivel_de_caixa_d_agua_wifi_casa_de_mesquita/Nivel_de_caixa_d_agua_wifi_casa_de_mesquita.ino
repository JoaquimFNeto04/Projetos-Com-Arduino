// casa dedei
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e55cb1172341437ebb236be67c85ab8e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Netvirtua_665";
char pass[] = "336144341";

#define caixa_boia_1 D2
#define caixa_boia_2 D3
#define caixa_boia_3 D4

#define NivelCaixa   V2

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
  if (digitalRead(caixa_boia_1)) nivel++;
  if (digitalRead(caixa_boia_2)) nivel++;
  if (digitalRead(caixa_boia_3)) nivel++;

  Serial.print (" NIVEL = ");
  Serial.println (nivel);

  if (nivel == 0) {

    Blynk.setProperty(NivelCaixa, "color", "#ff0000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O NIVEL  CRITICO");
  }

  if (nivel == 1) {

    Blynk.setProperty(NivelCaixa, "color", "#ff0000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  BAIXO ");
    delay (1000);
  }

  if (nivel == 2) {

    Blynk.setProperty(NivelCaixa, "color", "#FFA500");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  MEDIO ");
    delay (1000);

  }

  if (nivel == 3) {
    Blynk.setProperty(NivelCaixa, "color", "#008000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  CHEIO ");

    delay (1000);
  }
  Blynk.virtualWrite(NivelCaixa, nivel);
}
