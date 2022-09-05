#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define sensor_boia_1 A1
#define sensor_boia_2 A0
#define bomba 2

int controle;

int sensor1;
int sensor2;
int totaldeleitura = 0;

  // Inicializa o display no endereco 0x27
  LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


  void setup() {

  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
 
// put your setup code here, to run once:
  pinMode(sensor_boia_1,INPUT_PULLUP);
  pinMode(sensor_boia_2,INPUT_PULLUP);
  pinMode(bomba, OUTPUT);
  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print(" NIVEL DE CAIXA ");
  lcd.setCursor(0,1);
  lcd.print("CARREGANDO.    ");
  delay(250);
  lcd.print("CARREGANDO..    ");
  delay(250);
  lcd.print("CARREGANDO...   ");
  delay(250);
  lcd.print("CARREGANDO....  ");
  delay(250);
  lcd.print("CARREGANDO..... ");
  delay(250);
  lcd.print("CARREGANDO......");
  delay(250);
  Serial.println("LEITOR DE CAIXA D'AGUA");
  Serial.println("CARREGANDO");
  digitalWrite(bomba, LOW);
  delay(1000);
  
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
    Serial.println( "A CAIXA D'AGUA ESTA CHEIA.");
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("     CHEIA.     ");    
    digitalWrite(bomba, LOW);
  }

  if((sensor1==0)and(sensor2==1)){
    //erro
    Serial.println( "PROBLEMA EM UM DOS SENSORES");
    Serial.println( "LIGUE PARA ASSISTENCIA (83)3033-3391 ");
    lcd.setCursor(0,0);
    lcd.print(" O SENSOR  ESTA ");
    lcd.setCursor(0,1);
    lcd.print("    DEFEITO     ");        
    digitalWrite(bomba, LOW);    
  }

  if((sensor1==1)and(sensor2==0)){
    //leitura media
    Serial.println( "A CAIXA D'AGUA ESTA EM UM NIVEL INTERMEDIARIO.");
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("  PELA  METADE  ");    
  }

   if((sensor1==1)and(sensor2==1)){
    //vazio
    Serial.println( "A CAIXA D'AGUA ESTA EM UM NIVEL CRITICO.");
    lcd.setCursor(0,0);
    lcd.print("  A CAIXA ESTA  ");
    lcd.setCursor(0,1);
    lcd.print("     VAZIA.     ");    
    digitalWrite(bomba, HIGH);
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
