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

  int x1 = analogRead(SensorG1);// LEITURA DO SENSOR 1
 /* int x2 = analogRead(SensorG2);// LEITURA DO SENSOR 2
  int x3 = analogRead(SensorG3);// LEITURA DO SENSOR 3 */
    
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 1 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x1);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("O SENSOR 2 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x2);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("O SENSOR 3 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x3);
  delay(2000);
  lcd.clear();

  if ((x1 < 1400)&&(x2 < 1400)&&(x3 < 1400)){
  
  digitalWrite(Vgas, LOW);

  x1 = analogRead(SensorG1);// LEITURA DO SENSOR 1
  x2 = analogRead(SensorG2);// LEITURA DO SENSOR 2
  x3 = analogRead(SensorG3);// LEITURA DO SENSOR 3
    
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 1 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x1);
  lcd.setCursor(0,1);
  lcd.print(x1);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("O SENSOR 2 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x2);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("O SENSOR 3 MEDE ");
  lcd.setCursor(0,1);
  lcd.print(x3);
  delay(2000);
  lcd.clear();
    
  }
}
