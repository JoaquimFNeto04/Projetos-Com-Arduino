
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

byte led_azul = D0;
byte led_vermelho = D1;
byte led_verde_rele = D2;
byte buzzer = D3;

#define WLAN_SSID       "NCLOUD"
#define WLAN_PASS       ""

IPAddress ip(10, 0, 0, 51 );
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);

#include <MFRC522.h>
#include<SoftwareSerial.h>

#define SS_PIN 2
#define RST_PIN 15
#define No_Of_Card 3



MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial mySerial(8, 9);
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

char st[20];

char DEVID1[] = "vD6D4782E0999D11";// MARCOS HENRIQUE - ENTRADA PORTA 2 001
char DEVID2[] = "vEE0B76AAA0F6BD0";// JOAQUIM NETO - ENTRADA PORTA 2 002
char DEVID3[] = "vD19D827B12FA97E";// IVANILDO GARCIA - ENTRADA PORTA 2 003
char DEVID4[] = "v93C0A2A47F65BCC";// CAMILA FIRMINO - ENTRADA PORTA 2 004
char DEVID5[] = "v97F6089117BFA1C";// LUCAS - ENTRADA PORTA 2 005
char DEVID6[] = "v94F394FCB8B5D7D";// GIL ARAUJO - ENTRADA PORTA 2 006
char DEVID7[] = "vB149077BC1EFE24";// JUNIOR - ENTRADA PORTA 2 007
char DEVID8[] = "v0A8320ADCE5DAE8";// GEDEAN - ENTRADA PORTA 2 008
char DEVID9[] = "vF7D97539C2275A7";// TIAGO - ENTRADA PORTA 2 009
char DEVID10[] = "v41FA786B1B3D1AE";// JOSE VITORINO - ENTRADA PORTA 2 010
char DEVID11[] = "v95971692E7ADD5F";// RICHARDSON - ENTRADA PORTA 2 011
char DEVID12[] = "vFEE218456EBAB06";// ENTRADA NÃO AUTORIZADA PORTA 2

boolean DEBUG = true;

unsigned long askTimer = 0;

char serverName[] = "api.pushingbox.com";
boolean pinDevid1State = false;
boolean lastConnected = false;
int status = WL_IDLE_STATUS;

WiFiClient client;

void setup()
{
  Serial.begin(9600);
  WiFi.config(ip, gateway, subnet);

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

  pinMode(led_azul, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_verde_rele, OUTPUT);
  digitalWrite(led_verde_rele, HIGH);
  pinMode(buzzer, OUTPUT);

}

void loop() {

  cartaorf();
  blueled();

}
void blueled() {

  digitalWrite(led_azul, LOW);
  delay(25);
  digitalWrite(led_azul, HIGH);
  delay(750);

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

  if (conteudo.substring(1) == "00 CE 7D 51") // MARCOS HENRIQUE - ENTRADA PRINCIPAL 001
  {

  

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

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);

    

    sendToPushingBox(DEVID1);

  }

  else if (conteudo.substring(1) == "50 ED 6B 46") // JOAQUIM NETO - ENTRADA PRINCIPAL 002
  {

   
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JOAQUIM NETO - ENTRADA PRINCIPAL");
    Serial.println();
    

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);


    sendToPushingBox(DEVID2);
  }
  else if (conteudo.substring(1) == "B6 16 26 08") // IVANILDO GARCIA - ENTRADA PRINCIPAL 003
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("IVANILDO GARCIA - ENTRADA PRINCIPAL");
    Serial.println();
   

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);


    sendToPushingBox(DEVID3);
  }
  else if (conteudo.substring(1) == "7A 69 FD 05") // CAMILA FIRMINO - ENTRADA PRINCIPAL 004
  {

  
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("CAMILA FIRMINO - ENTRADA PRINCIPAL");
    Serial.println();
    

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);


    sendToPushingBox(DEVID4);
  }
  else if (conteudo.substring(1) == "4C 31 A9 AB") // LUCAS - ENTRADA PRINCIPAL 005
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("LUCAS - ENTRADA PRINCIPAL");
    Serial.println();
 

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);

    sendToPushingBox(DEVID5);
  }
  else if (conteudo.substring(1) == "7A 18 A9 AB")// GIL ARAUJO - ENTRADA PRINCIPAL 006
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("GIL ARAUJO - ENTRADA PRINCIPAL");
    Serial.println();
    

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);

    sendToPushingBox(DEVID6);
  }
  else if (conteudo.substring(1) == "CA 37 AA AB") // JUNIOR - ENTRADA PRINCIPAL 007
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JUNIOR - ENTRADA PRINCIPAL");
    Serial.println();
  

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);


    sendToPushingBox(DEVID7);
  }
  else if (conteudo.substring(1) == "C4 41 E9 F6") // GEDEAN - ENTRADA PRINCIPAL 008
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("GEDEAN - ENTRADA PRINCIPAL");
    Serial.println();
  

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);


    sendToPushingBox(DEVID8);
  }


  else if (conteudo.substring(1) == "40 ED A1 19") // TIAGO - ENTRADA PRINCIPAL 009
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("TIAGO - ENTRADA PRINCIPAL");
    Serial.println();
 

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);

    sendToPushingBox(DEVID9);

  }

  else if (conteudo.substring(1) == "30 16 6D 46") //JOSE VITORINO - ENTRADA PRINCIPAL 009
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("JOSE VITORINO - ENTRADA PRINCIPAL");
    Serial.println();
 

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);

    sendToPushingBox(DEVID10);

  }

   else if (conteudo.substring(1) == "A0 90 6D 46") //RICHARDSON - ENTRADA PRINCIPAL 011
  {

    
    Serial.println("Cartao identificado");
    Serial.println();
    Serial.println("RICHARDSON - ENTRADA PRINCIPAL");
    Serial.println();
 

    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);

    digitalWrite(led_verde_rele, LOW);
    digitalWrite(led_vermelho, HIGH);
    delay(1000);
    digitalWrite(led_verde_rele, HIGH);
    digitalWrite(led_vermelho, LOW);
    
    sendToPushingBox(DEVID11);

  }

  else {
   
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    
    sendToPushingBox(DEVID12);
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


