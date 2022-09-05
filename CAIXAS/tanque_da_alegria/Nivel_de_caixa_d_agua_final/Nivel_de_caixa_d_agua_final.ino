#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>
#include <SPI.h>

#define sensor_boia_1 A1
#define sensor_boia_2 A0
#define bombaled 8
#define bomba 2

int sensor1;
int sensor2;

  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,1,101);          //Define o endereco IP
  IPAddress gateway(192,168,1,1);      //Define o gateway
  IPAddress subnet(255,255,255,0); //Define a máscara de rede
  //Inicializa o servidor web na porta 8081
  EthernetServer server(8081);

  // Inicializa o display no endereco 0x27
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


  void setup() {

  //Inicializa a interface de rede
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
 
// put your setup code here, to run once:
  pinMode(sensor_boia_1,INPUT_PULLUP);
  pinMode(sensor_boia_2,INPUT_PULLUP);
  pinMode(bomba, OUTPUT);
  pinMode(bombaled, OUTPUT);
  digitalWrite(bomba, HIGH);
  digitalWrite(bombaled, LOW);
  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print(" NIVEL DE CAIXA ");
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO.    ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO..    ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO...   ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO....  ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO..... ");
  delay(250);
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO......");
  
}

void loop() {
  
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
