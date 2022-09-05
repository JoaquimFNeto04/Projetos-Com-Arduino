
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "edc2be4366c14a838de4285f064a537e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "casa";
char pass[] = "marcos10";

#define caixa_boia_1 D2
#define caixa_boia_2 D3
#define caixa_boia_3 D4
#define bomba D5
#define LEDVERDE D6
#define LEDAMARELO D7
#define LEDVERMELHO D8
#define NivelCaixa   V0

void setup() {

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(caixa_boia_1, INPUT_PULLUP);
  pinMode(caixa_boia_2, INPUT_PULLUP);
  pinMode(caixa_boia_3, INPUT_PULLUP);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARELO, OUTPUT);
  pinMode(LEDVERMELHO, OUTPUT);
  digitalWrite(bomba, HIGH);
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARELO, LOW);
  digitalWrite(LEDVERMELHO, LOW);


  WidgetLCD Display(V1);
  Display.clear();
  Display.print(1, 0, "O SISTEMA ESTA");
  Display.print (4, 1, "CARREGANDO");
  delay(2000);

}

void loop() {
  /*
    delay(1000);
    digitalWrite(LEDVERDE, LOW);
    digitalWrite(LEDAMARELO, LOW);
    digitalWrite(LEDVERMELHO, LOW);


    delay(1000);
    digitalWrite(LEDVERDE, HIGH);
    digitalWrite(LEDAMARELO, LOW);
    digitalWrite(LEDVERMELHO, LOW);
    digitalWrite(bomba, HIGH);

    delay(1000);
    digitalWrite(LEDVERDE, HIGH);
    digitalWrite(LEDAMARELO, HIGH);
    digitalWrite(LEDVERMELHO, LOW);


    delay(1000);
    digitalWrite(LEDVERDE, HIGH);
    digitalWrite(LEDAMARELO, HIGH);
    digitalWrite(LEDVERMELHO, HIGH);
    digitalWrite(bomba, LOW);
  */


  WidgetLCD Display(V1);
  Blynk.run();

  LeituraCaixa();

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
    digitalWrite(LEDVERDE, LOW);
    digitalWrite(LEDAMARELO, LOW);
    digitalWrite(LEDVERMELHO, HIGH);
    delay(500);
    digitalWrite(LEDVERMELHO, LOW);
    delay(500);
    digitalWrite(LEDVERMELHO, HIGH);
    delay(500);
    digitalWrite(LEDVERMELHO, LOW);
    delay(500);
  }

  if (nivel == 1) {

    Blynk.setProperty(NivelCaixa, "color", "#ff0000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  BAIXO ");

    digitalWrite(LEDVERDE, LOW);
    digitalWrite(LEDAMARELO, LOW);
    digitalWrite(LEDVERMELHO, HIGH);
    delay (2000);
  }

  if (nivel == 2) {

    Blynk.setProperty(NivelCaixa, "color", "#FFA500");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  MEDIO ");

    digitalWrite(LEDVERDE, LOW);
    digitalWrite(LEDAMARELO, HIGH);
    digitalWrite(LEDVERMELHO, LOW);
    delay (2000);

  }

  if (nivel == 3) {
    Blynk.setProperty(NivelCaixa, "color", "#008000");
    Display.clear();
    Display.print(0, 0, "A CAIXA ESTA COM");
    Display.print(0, 1, "O  NIVEL  CHEIO ");
    digitalWrite(bomba, HIGH);

    digitalWrite(LEDVERDE, HIGH);
    digitalWrite(LEDAMARELO, LOW);
    digitalWrite(LEDVERMELHO, LOW);
    delay (2000);
    Display.clear();
    Display.print(0, 0, " A  BOMBA  ESTA ");
    Display.print(0, 1, "   DESLIGADA    ");
    delay (1000);
  }
  Blynk.virtualWrite(NivelCaixa, nivel);
}
