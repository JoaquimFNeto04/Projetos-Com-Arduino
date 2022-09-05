
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para fazer a média
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para segundos
int Min = 00; //Variável para minutos
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão

int v1 = 0;
int v2 = 0;

#define WLAN_SSID       "grupo2gtec" // NOME DA REDE DE INTERNET
#define WLAN_PASS       "miguel2018" // SENHA DA REDE

/* IPAddress ip(192, 168, 15, 50 );
IPAddress gateway(192, 168, 15, 1);
IPAddress subnet(255, 255, 255, 0); */

#include<SoftwareSerial.h>

// INICIO DA CONFIGURAÇÃO PARA O AVISO POR VOZ
char st[20];

char DEVID1[] = "v530A88802C91B17";// SENSOR DO PORTÃO DA GARAGEM 1
char DEVID2[] = "vF90B0170F80D9FC";// SENSOR DO PORTÃO DA GARAGEM 1
char DEVID3[] = "v15638B729A9062E";// SENSOR DO PORTÃO DA GARAGEM 1
char DEVID4[] = "v788FF9DF4EFE452";// SENSOR DO PORTÃO DA GARAGEM 2
char DEVID5[] = "v5395FC833D2869B";// SENSOR DO PORTÃO DA GARAGEM 2
char DEVID6[] = "v69C1A1BE496DFF0";// SENSOR DO PORTÃO DA GARAGEM 2

boolean DEBUG = true;

unsigned long askTimer = 0;

char serverName[] = "api.pushingbox.com";
boolean pinDEVid1State = false;
boolean lastConnected = false;
int status = WL_IDLE_STATUS;
// FIM DA CONFIGURAÇÃO PARA O AVISO POR VOZ

WiFiClient client;

//CODIGO PARA O BLYNK
char auth[] = "a462c600abb6493ea70ea3b0f368a4e2";

void setup(){
 
  Blynk.begin(auth, WLAN_SSID, WLAN_PASS); 

 lcd.begin(16, 2);
 lcd.setCursor( 0, 0);
 lcd.print("Sensoriamento de");
 lcd.setCursor( 0, 1);
 lcd.print(" fluxo de Agua ");
 delay(3000);
 lcd.clear();
  
 pinMode(2, INPUT);
 attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) interrupção
  
  Serial.begin(9600);
  
  //WiFi.config(ip, gateway, subnet);
  
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

  

}

void loop() {

  Blynk.run();
  leitura();
  delay(2000);
}

void leitura(){

  WidgetLCD lcd0(V0);
  int portao_garagem1 = digitalRead(D1);
  int portao_garagem2 = digitalRead(D2);
  
  Serial.print("A PORTA ESTA: ");
  Serial.println(portao_garagem1);
  Serial.print("O valor de v1 e: ");
  Serial.println(v1);
  Serial.print("A PORTA ESTA: ");
  Serial.println(portao_garagem2);
  Serial.print("O valor de v2 e: ");
  Serial.println(v2);

  if (portao_garagem1 == 1) {
   
    if (v1 == 1){
   sendToPushingBox(DEVID1); // comando que manda a mensagem 
   Serial.println("A PORTA ESTA ABERTA");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500);  
  }

  if (v1 == 10){
   Serial.println("A PORTA 1 ESTA POR MAIS DE 20 SEGUNDOS");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "ABERTA A MAIS ");
   delay(2000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "DE 20 SEGUNDOS");   
  }

  if (v1 == 20){
   Serial.println("A PORTA 1 ESTA ABERTA");
   lcd0.clear();
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);      
  }

  if (v1 == 50){
   sendToPushingBox(DEVID3); // comando que manda a mensagem
   Serial.println("A PORTA DE GARAGEM 1 ABERTA POR MUITO TEMPO");
   lcd0.clear();
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);    
  }
   v1++; 
  }

  if ((portao_garagem1 == 0)&&(v1 == 0)){
   
   Serial.println("PORTAO FECHADA"); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "FECHADA");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "FECHADA");
   delay(1000);  
  }
  
  if ((portao_garagem1 == 0)&&(v1 != 0)){
  sendToPushingBox(DEVID2);
  Serial.println("A PORTA ESTA FECHADA"); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "FOI FECHADA");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 1 ESTA");
   lcd0.print(0, 1, "FOI FECHADA");
   delay(1000);  
  v1 = 0;
  }

  if (portao_garagem2 == 1) {
  
  if ( v2 == 1){
   sendToPushingBox(DEVID4); // comando que manda a mensagem 
   Serial.println("A PORTA ESTA ABERTA");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 FOI");
   lcd0.print(0, 1, "ABERTA");
   delay(500); 
  }

  if ( v2 == 10){
  
   Serial.println("A PORTA 2 ESTA POR MAIS DE 20 SEGUNDOS");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2");
   lcd0.print(0, 1, "ESTA ABERTA A MAIS ");
   delay(2000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "DE 20 SEGUNDOS");
  }

  if ( v2 == 20){
   
   Serial.println("A PORTA ESTA ABERTA POR MUITO TEMPO");
   lcd0.clear();
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);     
  }

  if ( v2 == 50){
   sendToPushingBox(DEVID6); // comando que manda a mensagem
   Serial.println("A PORTA ESTA ABERTA POR MUITO TEMPO");
   lcd0.clear();
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   delay(1000);
   lcd0.clear();
   delay(1000);
   lcd0.print(0, 0, "CUIDADO");
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "ABERTA A MUITO");
   delay(1000);
   lcd0.print(0, 1, "                ");   
   lcd0.print(0, 1, "TEMPO");
   delay(1000);    
  } 
  v2++;
 }

 if ((portao_garagem2 == 0)&&(v2 != 0)){
  sendToPushingBox(DEVID5);
  Serial.println("A PORTA FOI FECHADA"); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ");
   lcd0.print(0, 1, "FOI FECHADA");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ");
   lcd0.print(0, 1, "FOI FECHADA");
   delay(1000);
 }


 if ((portao_garagem2 == 0)&&(v2 == 0)){
   Serial.println("PORTA FECHADA"); 
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "FECHADA");
   delay(1000);
   lcd0.clear();
   lcd0.print(0, 0, "A PORTA 2 ESTA");
   lcd0.print(0, 1, "FECHADA");
   delay(1000);  
 } 
}

// FUNÇÃO PARA ENVIAR A NOTIFICAÇÃO
void sendToPushingBox(char DEVid[]) {

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
    client.print("GET /pushingbox?DEVid=");
    client.print(DEVid);
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


