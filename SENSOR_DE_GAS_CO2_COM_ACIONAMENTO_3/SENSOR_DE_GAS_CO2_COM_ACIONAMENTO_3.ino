/* PROJETO DE AUTOMAÇÃO PARA LEITURA E ACIONAMENTO DE CO2
 * EM UMA ESTUFA FEITA DE CONTEINNER PARA PLANTAÇÃO
 * DESENVOLVIDA POR JOAQUIM FIRMINO NETO DESENVOLVEDOR DE AUTOMAÇAO 
 * DO GRUPO 2G */

#include <Wire.h>
#include <LiquidCrystal_I2C.h> 


 // Inicializa o display no endereco 0x27
 LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

 #define Vanalog1 A0 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A0
 #define Vanalog2 A1 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A1
 #define Vanalog3 A2 // SENSOR DE GÁS NÚMERO 1 QUE ESTÁ LIGADO A PORTA A2
 #define Vgas 2 // PORTA QUE ACIONARA A VALVULA SOLENOIDE PARA LIBERAÇÃO DE CO2

 int SensorG1;
 int SensorG2;
 int SensorG3;

 int L = 1;
 

void setup() {

  Serial.begin(9600);
  pinMode(Vanalog1,INPUT);
  pinMode(Vanalog2,INPUT);
  pinMode(Vanalog3,INPUT);
  pinMode(Vgas,OUTPUT);
  digitalWrite(Vgas, HIGH);
  
  lcd.begin (16,2);

  lcd.setBacklight(HIGH);

}

void loop() {

  
  SensorG1 = (analogRead(Vanalog1)*(100/20));
  SensorG2 = (analogRead(Vanalog2)*(100/20));
  SensorG3 = (analogRead(Vanalog3)*(100/20));
  
  int CO2ppm = ((SensorG1+SensorG2+SensorG3)/3);

  if ((SensorG1 > 1400)&&(SensorG2 > 1400)&&(SensorG3 > 1400)) {

  digitalWrite(Vgas, HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 1 MEDE:");
  Serial.println("Sensor 1");
  lcd.setCursor(0,1);
  lcd.print(SensorG1);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG1);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 2 MEDE:");
  Serial.println("Sensor 2");
  lcd.setCursor(0,1);
  lcd.print(SensorG2);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG2);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 3 MEDE:");
  Serial.println("Sensor 3");
  lcd.setCursor(0,1);
  lcd.print(SensorG3);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG3);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A MEDIA E:");
  Serial.println("A media e ");
  lcd.setCursor(0,1);
  lcd.print(CO2ppm);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(CO2ppm);
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Leitura N ");
  Serial.println("Leitura Numero:");
  lcd.setCursor(0,1);
  lcd.print(L);
  Serial.println(L);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A VALVULA ESTA:");
  Serial.print("A VALVULA ESTA:");
  lcd.setCursor(0,1);
  lcd.println("DESLIGADA");
  Serial.print("DELIGADA");
  delay(3000);
    
  }
  else if ((SensorG1 < 1400)&&(SensorG2 < 1400)&&(SensorG3 < 1400)){

  digitalWrite(Vgas, LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 1 MEDE:");
  Serial.println("Sensor 1");
  lcd.setCursor(0,1);
  lcd.print(SensorG1);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG1);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 2 MEDE:");
  Serial.println("Sensor 2");
  lcd.setCursor(0,1);
  lcd.print(SensorG2);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG2);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("O SENSOR 3 MEDE:");
  Serial.println("Sensor 3");
  lcd.setCursor(0,1);
  lcd.print(SensorG3);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(SensorG3);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A MEDIA E:");
  Serial.println("A media e ");
  lcd.setCursor(0,1);
  lcd.print(CO2ppm);
  lcd.setCursor(13,1);
  lcd.print("PPM");
  Serial.println(CO2ppm);
  delay(3000);

  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Leitura Numero:");
  Serial.println("Leitura Numero:");
  lcd.setCursor(0,1);
  lcd.print(L);
  Serial.println(L);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A VALVULA ESTA:");
  Serial.print("A VALVULA ESTA:");
  lcd.setCursor(0,1);
  lcd.print("LIGADA");
  Serial.println("LIGADA");
  delay(3000);   
  } 

  if (L == 9999999999999999){
    L = 0;
  }
   else {
    L++;
   }
   
}
