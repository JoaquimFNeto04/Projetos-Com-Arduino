/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino Ethernet shield (W5100)
  to connect your project to Blynk.

  NOTE: Pins 10, 11, 12 and 13 are reserved for Ethernet module.
        DON'T use them in your sketch directly!

  WARNING: If you have an SD card, you may need to disable it
        by setting pin 4 to HIGH. Read more here:
        https://www.arduino.cc/en/Main/ArduinoEthernetShield

  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

#define W5100_CS  10
#define SDCARD_CS 4

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
  
  Blynk.begin(auth);
  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8442);
  // For more options, see Boards_Ethernet/Arduino_Ethernet_Manual example

  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);
  digitalWrite(30, HIGH);

  WidgetLCD lcd0(V0);  
  lcd0.clear();
  lcd0.print(1, 0, "O SISTEMA ESTA");
  lcd0.print(4, 1, "DESATIVADO");  
  
  WidgetLCD lcd(V1);  
  lcd.clear();
  lcd.print(1, 0, "O SISTEMA ESTA");
  lcd.print(4, 1, "CARREGANDO");
  delay(1000);
  lcd.clear();
  
  
}

void loop()
{
  Blynk.run();
  WidgetLCD lcd(V1);

  lcd.print(0, 0, "FAZENDO  LEITURA");
  lcd.print(0, 1, "DOS PORTOES");
  
  int gfe = digitalRead(39); // gfe = SENSOR DE GARAGEM FECHADO
  delay(200);
  int gab = digitalRead(40); // gab = SENSOR DE GARAGEM ABERTO
  delay(200);

  lcd.clear();
  lcd.print(0, 0, "PORTA DA GARAGEM");
   
  if ((gfe == 0) && (gab == 1)){  
    PortaoFechado();
    lcd.clear();
  }
  else if ((gfe == 1) && (gab == 0)){
  PortaoAberto();
  lcd.clear();
  }
  else if ((gfe == 1) && (gab == 1)){
  PortaoAbertoFechado();
  lcd.clear();
  }
}

void PortaoAberto (){

  WidgetLCD lcd(V1);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(5, 1, "ABERTO");
  delay(1000);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(5, 1, "ABERTO");
  delay(1000);  
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(5, 1, "ABERTO");
  delay(1000);
 }

void PortaoFechado (){

  WidgetLCD lcd(V1);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(4, 1, "FECHADO");
  delay(1000);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(4, 1, "FECHADO");
  delay(1000);  
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(4, 1, "FECHADO");
  delay(1000);
  }

void PortaoAbertoFechado (){

  WidgetLCD lcd(V1);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(0, 1, "ABRINDO/FECHANDO");
  delay(1000);
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(0, 1, "ABRINDO/FECHANDO");
  delay(1000);  
  lcd.print(0, 1, "                ");
  delay(500);
  lcd.print(0, 1, "ABRINDO/FECHANDO");
  delay(1000);
 }  
