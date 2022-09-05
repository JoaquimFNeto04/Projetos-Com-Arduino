// Programa : Envio de dados Arduino => Android  
// Autor : Arduino e Cia  
   
int contador = 0;  
int pinosensor = 7; //Ligado ao pino "coletor" do sensor optico  
int leitura; //Armazena o valor lido pelo sensor  
int pinpot = A0; //Ligado ao pino central do potenciometro  
   
void setup() 
{  
  pinMode(pinosensor, INPUT); //Define o pino do sensor como entrada  
  pinMode(pinpot, INPUT); //Define o pino do potenciometro como entrada   
  Serial.begin(9600);  

  //Envia o valor inicial zero do contador para o Android  
  Serial.write(201);   
  Serial.write(highByte(contador));  
  Serial.write(lowByte(contador));  
}  
   
void loop()  
{  
  //Le as informacoes do pino do sensor 
  leitura = digitalRead(pinosensor);  
  if (leitura != 1) //Verifica se o objeto foi detectado  
  {  
    contador = contador++; //Incrementa o valor do contador 

    //Loop caso o objeto pare sobre o sensor  
    while(digitalRead(pinosensor) != 1)  
    {  
      Serial.println(contador);  
      //Envia o valor atualizado do contador para o Android  
      Serial.write(201);  
      Serial.write(highByte(contador));  
      Serial.write(lowByte(contador));  
    }  
  }  

  //Envia as informacoes do potenciometro para o Android  
  int valor_pot = analogRead(pinpot);  
  Serial.write(202);  
  Serial.write(highByte(valor_pot));  
  Serial.write(lowByte(valor_pot));  
  delay(50);  
}  


