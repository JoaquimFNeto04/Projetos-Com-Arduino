/*
  DADOS DO MEGA QUE FOI PARA TIO GUSTAVO

  BN: Arduino/Genuino Mega or Mega 2560
  VID: 2341
  PID: 0042
  SN: 55639303634351419040
*/

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#define BLYNK_PRINT Serial

#define couller 23
int cont_couller = 0;
int cont_couller1 = 400;

// CAIXA D'AGUA E CISTERNA
#define NivelCisterna V0
#define NivelCaixa    V1

#define cisterna_boia_1 A0
#define cisterna_boia_2 A1
#define cisterna_boia_3 A2

#define caixa_boia_1 A3
#define caixa_boia_2 A4
#define caixa_boia_3 A5

//SENSORES DE PORTA ABERTA
#define SensorA 40
#define SensorB 41
#define SensorC 42
#define SensorD 43

// SISTEMA DE BARREIRAS ALARME

#define barreira_zona_1 19
#define barreira_zona_2 20
#define barreira_zona_3 21
#define sirene 22

int Alarme_zona_1 = 0;
int Alarme_zona_2 = 0;
int Alarme_zona_3 = 0;

int buttonState ;
int buttonStateP;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

void setup() {
  digitalWrite(sirene, HIGH);
  digitalWrite(couller, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);

  // Debug console

  Serial.begin(9600);

  Blynk.begin(auth);

  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  pinMode(cisterna_boia_1, INPUT_PULLUP);
  pinMode(cisterna_boia_2, INPUT_PULLUP);
  pinMode(cisterna_boia_3, INPUT_PULLUP);

  pinMode(caixa_boia_1, INPUT_PULLUP);
  pinMode(caixa_boia_2, INPUT_PULLUP);
  pinMode(caixa_boia_3, INPUT_PULLUP);

  pinMode(barreira_zona_1, INPUT);
  pinMode(barreira_zona_2, INPUT);
  pinMode(barreira_zona_3, INPUT);


  pinMode(SensorA, INPUT_PULLUP);
  pinMode(SensorB, INPUT_PULLUP);
  pinMode(SensorC, INPUT_PULLUP);
  pinMode(SensorD, INPUT_PULLUP);

  pinMode(sirene, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(couller, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(barreira_zona_1), zona1, CHANGE); //Configura o pino 19(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(barreira_zona_2), zona2, CHANGE); //Configura o pino 20(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(barreira_zona_3), zona3, CHANGE); //Configura o pino 21(Interrupção 0) para trabalhar como interrupção

  WidgetLCD portaaberta(V2);
  portaaberta.clear();
  portaaberta.print(1, 0, "O SISTEMA ESTA");
  portaaberta.print(4, 1, "CARREGANDO");
  delay(1000);

  WidgetLCD alarmes(V3);
  alarmes.clear();
  alarmes.print(1, 0, "O SISTEMA ESTA");
  alarmes.print(4, 1, "CARREGANDO");
  delay(1000);
}

void loop() {

  Blynk.run();
  LeituraCaixa();
  LeituraCisterna();

  WidgetLCD portaaberto(V2);
  WidgetLCD alarmes(V3);

  Serial.print(cont_couller);
  Serial.print(" e ");
  Serial.println(cont_couller1);


  if (buttonState == 0) {
    Serial.println("ALARME DESATIVADO");

    Alarme_zona_1 = 0;
    Alarme_zona_2 = 0;
    Alarme_zona_3 = 0;

    alarmes.clear();
    alarmes.print(0, 0, "OS ALARMES ESTAO");
    alarmes.print(0, 1, "   DESARMADOS   ");
    delay(2000);
    alarmes.clear();
    alarmes.print(0, 0, "    ATENCAO!    ");
    alarmes.print(0, 1, "    ATENCAO!    ");
    delay(2000);
  }

  if (buttonState != 0) {
    Serial.println("ALARME ATIVADO COM SUCESSO");

    alarmes.clear();
    alarmes.print(0, 0, "OS ALARMES ESTAO");
    alarmes.print(0, 1, "    ARMADOS!    ");
    delay(2000);
    AlarmesBarreiras();
  }

  if (buttonStateP == 0) {
    Serial.println("SENSORES DESATIVADO");

    portaaberto.clear();
    portaaberto.print(0, 0, "  OS  SENSORES  ");
    portaaberto.print(0, 1, "ESTAO DESARMADOS");
    delay(2000);
    portaaberto.clear();
    portaaberto.print(0, 0, "    ATENCAO!    ");
    portaaberto.print(0, 1, "    ATENCAO!    ");
    delay(2000);
  }

  if (buttonStateP != 0) {
    Serial.println("SENSOR DE PORTA ABERTA ATIVADO COM SUCESSO");

    portaaberto.clear();
    portaaberto.print(0, 0, "  OS  SENSORES  ");
    portaaberto.print(0, 1, " ESTAO  ARMADOS ");
    delay(2000);
    PortaAberta();
  }

  if (cont_couller != 400) {
    cont_couller ++;
    cont_couller1 = 0 ;
    digitalWrite(couller, 1);
  }
  if (cont_couller == 400) {
    cont_couller = 400;
    cont_couller1 ++;
    digitalWrite(couller, 0);
  }
  if (cont_couller1 == 400) {
    cont_couller = 0;
    cont_couller1 = 0;
    //digitalWrite(couller, 1);
  }


}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
}

BLYNK_WRITE(V4) {

  buttonState = param.asInt();

}

BLYNK_WRITE(V5) {

  buttonStateP = param.asInt();

}

void PortaAberta() {

  WidgetLCD portaaberto(V2);

  int Porta_Aberta_1 = digitalRead(SensorA);
  int Porta_Aberta_2 = digitalRead(SensorB);
  int Porta_Aberta_3 = digitalRead(SensorC);
  int Porta_Aberta_4 = digitalRead(SensorD);

  Serial.println("Porta 1 e ");
  Serial.println(Porta_Aberta_1);
  Serial.println("Porta 2 e ");
  Serial.println(Porta_Aberta_2);
  Serial.println("Porta 3 e ");
  Serial.println(Porta_Aberta_3);
  Serial.println("Porta 4 e ");
  Serial.println(Porta_Aberta_4);

  if ((Porta_Aberta_1 == 0) && (Porta_Aberta_2 == 0) && (Porta_Aberta_3 == 0) && (Porta_Aberta_4 == 0)) {

    portaaberto.clear();
    portaaberto.print(0, 0, " STATUS PORTOES ");
    portaaberto.print(0, 1, " TODOS FECHADOS ");
    delay(1000);

  }

  while ((Porta_Aberta_1 != 0) && (Porta_Aberta_2 == 0)) {


    portaaberto.clear();
    portaaberto.print(0, 0, "ATENCAO ATENCAO");
    portaaberto.print(0, 1, "PORTAO 1 ABERTA");
    Blynk.notify("ATENÇÃO, PORTA 1 FOI ABERTA");
    //digitalWrite(Portao2,HIGH);
    delay(1000);

  }

  while ((Porta_Aberta_2 != 0) && (Porta_Aberta_1 == 0)) {

    portaaberto.clear();
    portaaberto.print(0, 0, "ATENCAO ATENCAO");
    portaaberto.print(0, 1, "PORTAO 2 ABERTA");
    Blynk.notify("ATENÇÃO, PORTA 2 FOI ABERTA");
    //digitalWrite(Portao1,HIGH);
    delay(1000);
  }

  if (Porta_Aberta_3 != 0) {

    portaaberto.clear();
    portaaberto.print(0, 0, "ATENCAO ATENCAO");
    portaaberto.print(0, 1, "PORTAO 3 ABERTA");
    Blynk.notify("ATENÇÃO, PORTA 3 FOI ABERTA");
    delay(1000);
  }

  if (Porta_Aberta_4 != 0) {

    portaaberto.clear();
    portaaberto.print(0, 0, "ATENCAO ATENCAO");
    portaaberto.print(0, 1, "PORTAO 4 ABERTA");
    Blynk.notify("ATENÇÃO, PORTA 4 FOI ABERTA");
    delay(1000);
  }
}

void AlarmesBarreiras() {

  if ((Alarme_zona_1 == 0) && (Alarme_zona_2 == 0) && (Alarme_zona_3 == 0)) {

    WidgetLCD alarmes(V3);
    alarmes.clear();
    alarmes.print(0, 0, "TODAS  AS  ZONAS");
    alarmes.print(0, 1, " ESTAO  NORMAIS ");
    delay(2000);

  }

  if (Alarme_zona_1 == 1) {

    Blynk.notify("ATENÇÃO, ZONA 1 VIOLADA");
    WidgetLCD alarmes(V3);
    digitalWrite(sirene, LOW);
    alarmes.clear();
    alarmes.print(0, 0, "ATENCAO  ATENCAO");
    alarmes.print(0, 1, "DISPARO NA ZONA1");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA1");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA1");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA1");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
  }

  if (Alarme_zona_2 == 1) {

    Blynk.notify("ATENÇÃO, ZONA 2 VIOLADA");
    WidgetLCD alarmes(V3);
    digitalWrite(sirene, LOW);
    alarmes.clear();
    alarmes.print(0, 0, "ATENCAO  ATENCAO");
    alarmes.print(0, 1, "DISPARO NA ZONA2");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA2");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA2");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA2");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
  }

  if (Alarme_zona_3 == 1) {

    Blynk.notify("ATENÇÃO, ZONA 3 VIOLADA");
    WidgetLCD alarmes(V3);
    digitalWrite(sirene, LOW);
    alarmes.clear();
    alarmes.print(0, 0, "ATENCAO  ATENCAO");
    alarmes.print(0, 1, "DISPARO NA ZONA3");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA3");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA3");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA3");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
  }
}

void zona1() {

  Alarme_zona_1 = 1;

}

void zona2() {

  Alarme_zona_2 = 1;

}

void zona3() {

  Alarme_zona_3 = 1;

}

void LeituraCaixa() {
  int nivel = 1;
  if (digitalRead(caixa_boia_1)) nivel++;
  if (digitalRead(caixa_boia_2)) nivel++;
  if (digitalRead(caixa_boia_3)) nivel++;

  if (nivel == 1) {
    Blynk.setProperty(NivelCaixa, "color", "#ff0000");

  }

  if (nivel == 2) {
    Blynk.setProperty(NivelCaixa, "color", "#FFA500");

  }

  if (nivel == 3) {
    Blynk.setProperty(NivelCaixa, "color", "#ffff00");

  }
  if (nivel == 4) {
    Blynk.setProperty(NivelCaixa, "color", "#008000");

  }

  Blynk.virtualWrite(NivelCaixa, nivel);
}

void LeituraCisterna() {
  int nivel = 1;
  if (digitalRead(cisterna_boia_1)) nivel++;
  if (digitalRead(cisterna_boia_2)) nivel++;
  if (digitalRead(cisterna_boia_3)) nivel++;

  if (nivel == 1) {
    Blynk.setProperty(NivelCisterna, "color", "#ff0000");

  }

  if (nivel == 2) {
    Blynk.setProperty(NivelCisterna, "color", "#FFA500");

  }

  if (nivel == 3) {
    Blynk.setProperty(NivelCisterna, "color", "#ffff00");

  }
  if (nivel == 4) {
    Blynk.setProperty(NivelCisterna, "color", "#008000");

  }
  Blynk.virtualWrite(NivelCisterna, nivel);
}
