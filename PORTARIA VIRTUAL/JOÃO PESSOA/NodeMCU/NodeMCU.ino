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
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "INSERIR TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NCLOUD";
char pass[] = "miguel20";


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  pinMode(D7, INPUT_PULLUP);
  pinMode(D8, INPUT_PULLUP);
  pinMode(D9, INPUT_PULLUP);
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
  
  int portaobaixo = digitalRead(D7);
  delay(500);
  int portaopedestre = digitalRead(D8);
  delay(500);
  int portaocima = digitalRead(D9);
  delay(500);

  lcd.clear();
  lcd.print(0, 0, "PORTAO DE CIMA");
   
  if (portaocima == 0){  
    PortaoAberto();
    lcd.clear();
  }
  else{
  PortaoFechado();
  lcd.clear();
  }

  lcd.print(0, 0, "PORTAO DE BAIXO");
   
  if (portaobaixo == 0){  
    PortaoAberto();
    lcd.clear();
  }
  else{
  PortaoFechado();
  lcd.clear();
  }

  lcd.print(0, 0, "PORTAO  PEDESTRE");
   
  if (portaopedestre == 0){  
    PortaoAberto();
    lcd.clear();
  }
  else{
  PortaoFechado();
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
