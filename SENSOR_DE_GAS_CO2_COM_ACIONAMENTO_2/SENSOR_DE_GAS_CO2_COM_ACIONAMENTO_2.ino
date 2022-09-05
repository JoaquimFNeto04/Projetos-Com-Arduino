/* PROJETO DE AUTOMAÇÃO PARA LEITURA E ACIONAMENTO DE CO2
 * EM UMA ESTUFA FEITA DE CONTEINNER PARA PLANTAÇÃO
 * DESENVOLVIDA POR JOAQUIM FIRMINO NETO DESENVOLVEDOR DE AUTOMAÇAO 
 * DO GRUPO 2G */

#include <Wire.h>
#include <LiquidCrystal_I2C.h> 


 // Inicializa o display no endereco 0x27
 LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

 #define SensorG1 A0 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A0
 #define SensorG2 A1 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A1
 #define SensorG3 A2 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A2
 #define Vgas 1 // PORTA QUE ACIONARA A VALVULA SOLENOIDE PARA LIBERAÇÃO DE CO2

 int RL = 20;
 int RO = 10;
 double RS1;
 double RS2;
 int CO2ppm1;
 int CO2ppm2;
 int CO2ppm3;
 double Vanalog1;
 double Vanalog2;
 double Vanalog3;
 double ratio;
 
 

void setup() {

  pinMode(SensorG1,INPUT);
  pinMode(SensorG2,INPUT);
  pinMode(SensorG3,INPUT);
  pinMode(Vgas,OUTPUT);
  digitalWrite(Vgas, HIGH);
  
  lcd.begin (16,2);

  lcd.setBacklight(HIGH);

}

void loop() {

  Vanalog1 = (analogRead(SensorG1)*(5/1023));
  RS1 = (RL*(5-Vanalog1)/Vanalog1);

  Vanalog2 = (analogRead(SensorG2)*(5/1023));
  RS2 = (RL*(5-Vanalog2)/Vanalog2);

  int ratio1 = RS1/RO;
  int ratio2 = RS2/RO;

  CO2ppm1 = 37143 * pow(ratio1, -3.178);
  CO2ppm2 = 37143 * pow(ratio2, -3.178);
  
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 1 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(CO2ppm1);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("O SENSOR 2 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(CO2ppm2);
  delay(2000);
  lcd.clear();
 }
