#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include<SoftwareSerial.h>

#define WLAN_SSID  "valesilicio"
#define WLAN_PASS  "marcos10"

WiFiClient client;

void setup() {

  Serial.begin(9600);

  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D8, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);

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

  int v0 = digitalRead(D0);
  int v1 = digitalRead(D1);
  int v2 = digitalRead(D2);
  int v3 = digitalRead(D3);
  int v4 = digitalRead(D4);
  int v5 = digitalRead(D5);
  int v6 = digitalRead(D6);
  int v7 = digitalRead(D7);
  int v8 = digitalRead(D8);
  int A0 = digitalRead(A0);

  Serial.print ("D0 = ");
  Serial.println (v0);
  Serial.print ("D1 = ");
  Serial.println (v1);
  Serial.print ("D2 = ");
  Serial.println (v2);
  Serial.print ("D3 = ");
  Serial.println (v3);
  Serial.print ("D4 = ");
  Serial.println (v4);
  Serial.print ("D5 = ");
  Serial.println (v5);
  Serial.print ("D6 = ");
  Serial.println (v6);
  Serial.print ("D7 = ");
  Serial.println (v7);
  Serial.print ("D8 = ");
  Serial.println (v8);
  Serial.print ("A0 = ");
  Serial.println (0);
  Serial.println (" ");
  delay(1500);
}
