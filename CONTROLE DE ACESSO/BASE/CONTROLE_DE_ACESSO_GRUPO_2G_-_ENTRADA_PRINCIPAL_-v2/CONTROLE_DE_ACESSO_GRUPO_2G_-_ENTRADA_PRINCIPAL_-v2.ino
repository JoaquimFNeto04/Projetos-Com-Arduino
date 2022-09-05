
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#define BLYNK_PRINT Serial
//#include <BlynkSimpleEsp8266.h>

//char auth[] = "dd4b9916c297431b89d5d13a54a9b612";

#define WLAN_SSID       "grupo2g"
#define WLAN_PASS       "miguel2018"

/*
  IPAddress ip(192, 168, 15, 50 );
  IPAddress gateway(192, 168, 15, 1);
  IPAddress subnet(255, 255, 255, 0);
*/

#include <MFRC522.h>
#include<SoftwareSerial.h>

#define porta D0
#define SS_PIN D1
#define RST_PIN D2
#define buzzer A0
//#define botvirtual D3
#define No_Of_Card 5


MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial mySerial(8, 9);
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

// INICIO DA CONFIGURAÇÃO PARA O AVISO POR VOZ
char st[20];

char DEVID1[] = "v1CA805EB52FBA64";// MARCOS HENRIQUE - ENTRADA PRINCIPAL 001
char DEVID2[] = "v29ECB7811A899ED";// JOAQUIM NETO - ENTRADA PRINCIPAL 002
char DEVID3[] = "v665A4BEC4EA443B";// IVANILDO GARCIA - ENTRADA PRINCIPAL 003
char DEVID4[] = "v2D64FF2C6B0216A";// CAMILA FIRMINO - ENTRADA PRINCIPAL 004
char DEVID5[] = "v73A0229AED63CC0";// LUCAS - ENTRADA PRINCIPAL 005
char DEVID6[] = "v866E10D711E5B5F";// GIL ARAUJO - ENTRADA PRINCIPAL 006
char DEVID7[] = "vCAC41FCB77E0E2A";// JUNIOR - ENTRADA PRINCIPAL 007
char DEVID8[] = "v2B4AB699C6D4959";// GEDEAN - ENTRADA PRINCIPAL 008
char DEVID9[] = "v262DDAB24BB59B2";// WELLINGTON - ENTRADA PRINCIPAL 009
char DEVID10[] = "v10B40D89E38617C";// JOSE VITORINO - ENTRADA PRINCIPAL 010
char DEVID11[] = "v55583957D865579";// RICHARDSON - ENTRADA PRINCIPAL 011
char DEVID12[] = "v66D158E2BD88AFF";// ENTRADA NÃO AUTORIZADA

boolean DEBUG = true;

unsigned long askTimer = 0;

char serverName[] = "api.pushingbox.com";
boolean pinDevid1State = false;
boolean lastConnected = false;
int status = WL_IDLE_STATUS;
// FIM DA CONFIGURAÇÃO PARA O AVISO POR VOZ

WiFiClient client;

void setup() {
  Serial.begin(9600);
  //  WiFi.config(ip, gateway, subnet);
  //Blynk.begin(auth, WLAN_SSID, WLAN_PASS);

  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

  pinMode(buzzer, OUTPUT);
  pinMode(porta, OUTPUT);
 // pinMode(botvirtual, INPUT);
 digitalWrite(porta, HIGH);


}

void loop() {

  //Blynk.run();

  if (WiFi.status() != WL_CONNECTED) {
    //  WiFi.config(ip, gateway, subnet);

    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();

    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
 /*  int botvirtual2 = digitalRead(botvirtual);

 if (botvirtual2 == 1) {

    digitalWrite(porta, LOW);
    Serial.println("PORTA ABERTA PELO APP");

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

    delay(2000);
    digitalWrite(porta, HIGH);
  }*/
  cartaorf();
}

void cartaorf() {

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");

  conteudo.toUpperCase();

  if (conteudo.substring(1) == "50 91 1B A8") // MARCOS HENRIQUE - ENTRADA PRINCIPAL 001
  {


    digitalWrite(porta, LOW);
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("MARCOS HENRIQUE - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID1);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

  }

  else if (conteudo.substring(1) == "50 ED 6B 46") // JOAQUIM NETO - ENTRADA PRINCIPAL 002
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JOAQUIM NETO - ENTRADA PRINCIPAL");
    Serial.println();

    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID2);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
  else if (conteudo.substring(1) == "B6 16 26 08") // IVANILDO GARCIA - ENTRADA PRINCIPAL 003
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("IVANILDO GARCIA - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID3);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

  }
  else if (conteudo.substring(1) == "7A 69 FD 05") // CAMILA FIRMINO - ENTRADA PRINCIPAL 004
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("CAMILA FIRMINO - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID4);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
  else if (conteudo.substring(1) == "4C 31 A9 AB") // LUCAS - ENTRADA PRINCIPAL 005
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("LUCAS - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID5);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
  else if (conteudo.substring(1) == "30 80 AD 19")// GIL ARAUJO - ENTRADA PRINCIPAL 006
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("GIL ARAUJO - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID6);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
  else if (conteudo.substring(1) == "CA 37 AA AB") // JUNIOR - ENTRADA PRINCIPAL 007
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JUNIOR - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID7);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }
  else if (conteudo.substring(1) == "C4 41 E9 F6") // GEDEAN - ENTRADA PRINCIPAL 008
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("GEDEAN - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID8);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }


  else if (conteudo.substring(1) == "40 ED A1 19") // TIAGO - ENTRADA PRINCIPAL 009
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("WELLINGTON DA SILVA - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID9);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

  }

  else if (conteudo.substring(1) == "13 F9 FA 29") //JOSE VITORINO - ENTRADA PRINCIPAL 009
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JOSE VITORINO - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID10);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

  }

  else if (conteudo.substring(1) == "A0 90 6D 46") //WELLINGTON - ENTRADA PRINCIPAL 011
  {


    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("WELLINGTON DA SILVA - ENTRADA PRINCIPAL");
    Serial.println();


    digitalWrite(porta, LOW);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID11);

    delay(1700);
    digitalWrite(porta, HIGH);

    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();

  }

  else {

    Serial.println("Cartao nao identificado");

    digitalWrite(porta, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);

    sendToPushingBox(DEVID12);


    Serial.println();
    Serial.println("Aproxime o seu cartao do leitor...");
    Serial.println();
  }

  if (client.available()) {
    char c = client.read();
    if (DEBUG) {
      Serial.print(c);
    }
  }
  if (!client.connected() && lastConnected) {
    if (DEBUG) {
      Serial.println();
    }
    if (DEBUG) {
      Serial.println("disconnecting.");
    }
    client.stop();
  }
  lastConnected = client.connected();
}

void sendToPushingBox(char devid[]) {

  client.stop(); if (DEBUG) {
    Serial.println("connecting...");
  }
  if (client.connect(serverName, 80)) {
    if (DEBUG) {
      Serial.println("connected");
    }
    if (DEBUG) {
      Serial.println("sendind request");
    }
    client.print("GET /pushingbox?devid=");
    client.print(devid);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();
  }
  else {
    if (DEBUG) {
      Serial.println("connection failed");
    }
  }
}


