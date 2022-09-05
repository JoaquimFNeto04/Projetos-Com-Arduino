
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


byte led_azul = D0;
byte led_vermelho = D4;
byte led_verde_rele = D2;
byte buzzer = D3;


#define WLAN_SSID       "grupo2gtec"
#define WLAN_PASS       "miguel2018"

/*
IPAddress ip(192, 168, 15, 50 );
IPAddress gateway(192, 168, 15, 1);
IPAddress subnet(255, 255, 255, 0);
*/

#include <MFRC522.h>
#include<SoftwareSerial.h>

#define SS_PIN D1
#define RST_PIN 15
#define No_Of_Card 3



MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial mySerial(8, 9);
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

// INICIO DA CONFIGURAÇÃO PARA O AVISO POR VOZ
char st[20];

char DEVID1[] = "vD31362B4F2F3A2E";// MARCOS HENRIQUE - ENTRADA PRINCIPAL 001
char DEVID2[] = "v766348F3F93C810";// JOAQUIM NETO - ENTRADA PRINCIPAL 002
char DEVID3[] = "v5E0179B488C0EE5";// IVANILDO GARCIA - ENTRADA PRINCIPAL 003
char DEVID4[] = "v1F7D41971644917";// CAMILA FIRMINO - ENTRADA PRINCIPAL 004
char DEVID5[] = "vC5A0405F79B93FD";// LUCAS - ENTRADA PRINCIPAL 005
char DEVID6[] = "v9BD5BC88861F515";// GIL ARAUJO - ENTRADA PRINCIPAL 006
char DEVID7[] = "vCAC41FCB77E0E2A";// JUNIOR - ENTRADA PRINCIPAL 007
char DEVID8[] = "v2B4AB699C6D4959";// GEDEAN - ENTRADA PRINCIPAL 008
char DEVID9[] = "v6EABC5059BEA2C5";// TIAGO - ENTRADA PRINCIPAL 009
char DEVID10[] = "vE3AEF3EFA7E13AB";// JOSE VITORINO - ENTRADA PRINCIPAL 010
char DEVID11[] = "v55583957D865579";// RICHARDSON - ENTRADA PRINCIPAL 011
char DEVID12[] = "vDE78CA92D47364F";// ENTRADA NÃO AUTORIZADA

boolean DEBUG = true;

unsigned long askTimer = 0;

char serverName[] = "api.pushingbox.com";
boolean pinDevid1State = false;
boolean lastConnected = false;
int status = WL_IDLE_STATUS;
// FIM DA CONFIGURAÇÃO PARA O AVISO POR VOZ

WiFiClient client;

void setup()
{
  Serial.begin(9600);
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


