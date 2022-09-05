#include <SPI.h>
#include <Ethernet.h>
 
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x9B, 0x36 }; //Endereco fisico de MAC
byte ip[] = { 192, 168, 1, 101 }; // ip na lan
byte gateway[] = { 192, 168, 0, 1 }; // ip do roteador
byte subnet[] = { 255, 255, 255, 0 }; //mascara
EthernetServer server(8081); //Porta do Servidor a ser usada

String readString;
 
int pinoRele = 9; //pino usado pelo rele
boolean ligado = true;
 
//////////////////////
 
void setup(){
 
  pinMode(pinoRele, OUTPUT); //seta o pino do relé como saida
  //Inicia a biblioteca de Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  //inicia o Servidor
  server.begin();
 
  //Serial
  Serial.begin(9600);
  Serial.println("Arduino e Android Automação Residencial Simples"); // so I can keep track of what is loaded
}
 
void loop(){
  // Cria uma conexao do tipo Cliente
  EthernetClient client = server.available();
  //verifica se ha conexao de algum dispositivo como cliente
  //se sim prepara para receber os dados
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        //le caracter por caracter via HTTP request
        if (readString.length() < 100) {
 
         
          // armazena os caracteres em um String
          readString += c;
 
        }
 
        //verifica se o dados recebidos terminos
        //com '\n' que representa enter
        if (c == '\n') {
 
          // controla o pino do arduino
          Serial.println(readString); //imprime o valor na serial para verificacao
          if(readString.indexOf("?ligarlampada") >0)//verifica se a string recebida contem a frase ?ligarlampada
          {
            digitalWrite(pinoRele, HIGH);    // deixa o pino do relé em estado Alto
            Serial.println("Ligado");
            ligado = false;
          }
          else{
            if(readString.indexOf("?desligarlampada") >0)//verifica se a string recebida contem a frase ?desligarlampada
            {
              digitalWrite(pinoRele, LOW);     // deixa o pino do relé em estado Baixo
              Serial.println("Desligado");
              ligado = true;
            }
          }
          //limpa a String para verificar o novo status recebidos
          readString="";
 
 
   
 
          client.println("HTTP/1.1 200 OK"); //codigo padrao para a criacao da pagina
          client.println("Content-Type: text/html");
          client.println();
 
          client.println("<html>");
          //client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          client.println("<head>");
          client.println("<title>Arduino e Android </title>");
       
 
          client.println("<link rel='stylesheet' type='text/css' href='http://www.tecnologiaeciencia.com.br/arduino/AutomacaoEstilo.css' />"); //link do CSS da pagina (pode ser baixado e alterado)
          client.println("<script type='text/javascript' src='http://www.tecnologiaeciencia.com.br/arduino/EstadoRele.js'></script>"); //link para o javascript da pagina
          client.println("</head>");
          client.println("<body>");
          client.println("<div id='wrapper'>Arduino e Android Automacao Simples"); //layoout
          client.print("<div id='rele'></div><div id='estado' style='visibility: hidden;'>");
          client.print(ligado);
          client.println("</div>");
          client.println("<div id='botao'></div>");//chama a div do botao
          client.println("</div>");
          client.println("<script>EstadoRele()</script>");//realiza a chamada do metodo do Javascript
          client.println("</body>");
          client.println("</head>");
 
          delay(1);
          //para a recepcao e envio de dados por parte do cliente
          client.stop();
 
 
 
        }
      }
    }
  }
}
