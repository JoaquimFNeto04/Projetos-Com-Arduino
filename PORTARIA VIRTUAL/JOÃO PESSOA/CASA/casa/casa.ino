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

#define sensor_boia_cima_1 D0
#define sensor_boia_cima_2 D1
#define sensor_boia_baixo_1 D2
#define sensor_boia_baixo_2 D3
#define bombaled D4
#define bomba D5
int sensor1;
int sensor2;


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Inicializa o display no endereco 0x27
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
  WidgetLCD LCD_B(V1);
  pinMode(sensor_boia_cima_1, INPUT_PULLUP);// sensor de cima cheio
  pinMode(sensor_boia_cima_2, INPUT_PULLUP);// sensor de cima vazio
  pinMode(sensor_boia_baixo_1, INPUT_PULLUP);// sensor de baixo cheio
  pinMode(sensor_boia_baixo_2, INPUT_PULLUP);// sensor de baixo vazio
  pinMode(bombaled, OUTPUT);
  pinMode(bomba, OUTPUT);
  digitalWrite(bomba, HIGH);
  digitalWrite(bombaled, LOW);

  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print(" NIVEL DE CAIXA ");
  LCD_B.print(1, 0, " NIVEL DE CAIXA ");
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO.    ");
  LCD_B.print(0, 1, "CARREGANDO.    ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO..    ");
  LCD_B.print(0, 1, "CARREGANDO..    ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO...   ");
  LCD_B.print(0, 1, "CARREGANDO...   ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO....  ");
  LCD_B.print(0, 1, "CARREGANDO....  ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO..... ");
  LCD_B.print(0, 1, "CARREGANDO..... ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO......");
  LCD_B.print(0, 1, "CARREGANDO......");
  lcd.clear();
}

void loop()
{
 
  Blynk.run();
  delay(2000);

  // faz as leituras maxima e minima das boias:
  int leitura_sens_Max=analogRead(sensor_boia_1);
  int leitura_sens_Min=analogRead(sensor_boia_2);
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  if(leitura_sens_Max<100){
    sensor1=1;
  }else{
    sensor1=0;
  }
  if(leitura_sens_Min<100){
    sensor2=1;
  }else{
    sensor2=0;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
   if((sensor1==0)and(sensor2==0)){
    //tanque cheio
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("     CHEIA.     ");    
    digitalWrite(bombaled, LOW);
    digitalWrite(bomba, HIGH);
    Cheio();
  }

  if((sensor1==0)and(sensor2==1)){
    //erro
    lcd.setCursor(0,0);
    lcd.print(" O SENSOR  ESTA ");
    lcd.setCursor(0,1);
    lcd.print("    DEFEITO     ");        
    digitalWrite(bombaled, LOW);    
    digitalWrite(bomba, HIGH);
    Defeito();
  }

  if((sensor1==1)and(sensor2==0)){
    //leitura media
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("  PELA  METADE  ");
    Medio();   
  }

   if((sensor1==1)and(sensor2==1)){
    //vazio
    
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("     VAZIA.     ");    
    digitalWrite(bombaled, HIGH);
    digitalWrite(bomba, LOW);
    Vazio();
  } 

/*
  Serial.print("O total de leitura e = ");
  totaldeleitura ++;
  Serial.println(totaldeleitura);
  Serial.println(" ");
  
  Serial.println(" ");  
  Serial.print("Sensor de cima e = ");
  Serial.print(leitura_sens_Max);
  Serial.print(" e o Sensor de baixo e = ");
  Serial.print(leitura_sens_Min);
  Serial.print(" O valor do sensor de cima e = ");  
  Serial.print(sensor1);
  Serial.print(" E valor do sensor de baixo e = ");  
  Serial.println(sensor2);  
  Serial.println(" ");  */

}

void Defeito(){

//Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
          client.println("Connection: close");
          client.println("Refresh: 4"); //Recarrega a pagina a cada 4seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.println("<table width=\"100%\" border=\"0\">");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th scope=\"col\"><img src='http://automacao.grupo2g.com.br/defeito.png' width=\"488\" height=\"362\" /></th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th align=\"center\" valign=\"top\" scope=\"col\"> A BOMBA ESTÁ DESLIGADA</th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("</table>");
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }  

 }

void Cheio(){

//Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
          client.println("Connection: close");
          client.println("Refresh: 4"); //Recarrega a pagina a cada 4seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.println("<table width=\"100%\" border=\"0\">");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th scope=\"col\"><img src='http://automacao.grupo2g.com.br/caixa_cheia.png' width=\"488\" height=\"362\" /></th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th align=\"center\" valign=\"top\" scope=\"col\"> A BOMBA ESTÁ DESLIGADA</th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("</table>");
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }  
}

void Medio(){

//Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
          client.println("Connection: close");
          client.println("Refresh: 4"); //Recarrega a pagina a cada 4seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.println("<table width=\"100%\" border=\"0\">");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th scope=\"col\"><img src='http://automacao.grupo2g.com.br/caixa_medio.png' width=\"488\" height=\"362\" /></th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th align=\"center\" valign=\"top\" scope=\"col\"> NÃO FOI POSSIVEL LER O STATUS DA BOMBA</th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("</table>");
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    } 
}

void Vazio(){

//Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
          client.println("Connection: close");
          client.println("Refresh: 4"); //Recarrega a pagina a cada 4seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.println("<table width=\"100%\" border=\"0\">");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th scope=\"col\"><img src='http://automacao.grupo2g.com.br/caixa_vazia.png' width=\"488\" height=\"362\" /></th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("<tr>");
          client.println("<td><table width=\"50%\" border=\"0\" align=\"center\">");
          client.println("<tr>");
          client.println("<th align=\"center\" valign=\"top\" scope=\"col\"> A BOMBA ESTÁ LIGADA</th>");
          client.println("</tr>");
          client.println("</table></td>");
          client.println("</tr>");
          client.println("</table>");
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }
}
