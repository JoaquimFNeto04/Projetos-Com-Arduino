/* 
DADOS DO MEGA QUE FOI PARA TIO GUSTAVO

BN: Arduino/Genuino Mega or Mega 2560
VID: 2341
PID: 0042
SN: 55639303035351B0F102
*/

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#define BLYNK_PRINT Serial


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

#define Portao1 23
#define Portao2 24

int Porta1 = 0;
int Porta2 = 0;

// SISTEMA DE BARREIRAS ALARME
#define barreira_zona_1 18
#define barreira_zona_2 19
#define barreira_zona_3 20
#define barreira_zona_4 21
#define sirene 22

int Alarme_zona_1 = 0;
int Alarme_zona_2 = 0;
int Alarme_zona_3 = 0;
int Alarme_zona_4 = 0;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

void setup() {
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
  pinMode(barreira_zona_4, INPUT);

  pinMode(SensorA, INPUT_PULLUP);
  pinMode(SensorB, INPUT_PULLUP);
  pinMode(SensorC, INPUT_PULLUP);
  pinMode(SensorD, INPUT_PULLUP);

  pinMode(sirene, OUTPUT);
  pinMode(Portao1, OUTPUT);
  pinMode(Portao2, OUTPUT);
  digitalWrite(Portao1, HIGH);
  digitalWrite(Portao2, HIGH);
  digitalWrite(sirene, HIGH);

  attachInterrupt(digitalPinToInterrupt(barreira_zona_1), zona1, FALLING); //Configura o pino 18(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(barreira_zona_2), zona2, FALLING); //Configura o pino 19(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(barreira_zona_3), zona3, FALLING); //Configura o pino 20(Interrupção 0) para trabalhar como interrupção
  attachInterrupt(digitalPinToInterrupt(barreira_zona_4), zona4, FALLING); //Configura o pino 21(Interrupção 0) para trabalhar como interrupção

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
  //AlarmesBarreiras();
  //PortaAberta();
  LeituraCaixa();
  LeituraCisterna();

}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V5);
}
BLYNK_WRITE(V5) {

  Alarme_zona_1 = 0;
  Alarme_zona_2 = 0;
  Alarme_zona_3 = 0;
  Alarme_zona_4 = 0;

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

  while ((Porta_Aberta_1 != 0)&& (Porta_Aberta_2 == 0)){

    
    portaaberto.clear();
    portaaberto.print(0, 0, "ATENCAO ATENCAO");
    portaaberto.print(0, 1, "PORTAO 1 ABERTA");
    Blynk.notify("ATENÇÃO, PORTA 1 FOI ABERTA");
    //digitalWrite(Portao2,HIGH);
    delay(1000);
    
  }

  while ((Porta_Aberta_2 != 0)&& (Porta_Aberta_1 == 0)) {

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

  if ((Alarme_zona_1 == 0) && (Alarme_zona_2 == 0) && (Alarme_zona_3 == 0) && (Alarme_zona_4 == 0)) {

    WidgetLCD alarmes(V3);
    alarmes.clear();
    alarmes.print(0, 0, "TODAS  AS  ZONAS");
    alarmes.print(0, 1, " ESTAO  NORMAIS ");

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

  if (Alarme_zona_4 == 1) {

    Blynk.notify("ATENÇÃO, ZONA 4 VIOLADA");
    WidgetLCD alarmes(V3);
    digitalWrite(sirene, LOW);
    alarmes.clear();
    alarmes.print(0, 0, "ATENCAO  ATENCAO");
    alarmes.print(0, 1, "DISPARO NA ZONA4");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA4");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA4");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
    delay(500);
    digitalWrite(sirene, LOW);
    alarmes.print(0, 1, "DISPARO NA ZONA4");
    delay(500);
    digitalWrite(sirene, HIGH);
    alarmes.print(0, 1, "                ");
  }
}

void zona1() {

  Alarme_zona_1 = 1;
  digitalWrite(Portao2,HIGH);

}

void zona2() {

  Alarme_zona_2 = 1;

}

void zona3() {

  Alarme_zona_3 = 1;

}

void zona4() {

  Alarme_zona_4 = 1;

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
