#include <SoftwareSerial.h>//
 SoftwareSerial mySerial(10, 11); // 2-RX, 3-TX

int ch1 = 4;
int ch2 = 5;
int ch3 = 6;
int ch4 = 7;

 void setup()
 {
 mySerial.begin(9600);
 pinMode(ch1, OUTPUT);//Pino digital saÃ­da do Arduino(4-ch1);
 pinMode(ch2, OUTPUT);//Pino digital saÃ­da do Arduino(5-ch2);
 pinMode(ch3, OUTPUT);//Pino digital saÃ­da do Arduino(6-ch3);
 pinMode(ch4, OUTPUT);//Pino digital saÃ­da do Arduino(7-ch4);
 }

 void loop() 
{
 char caracter = mySerial.read();
 //--------------------------------ch1---------------------
 if(caracter == 'A')
{
 digitalWrite(ch1,HIGH);
}

if(caracter == 'B')
{
 digitalWrite(ch1,LOW);
}
//---------------------------------ch1----------------------
//---------------------------------ch2---------------------
 if(caracter == 'C')
{
 digitalWrite(ch2,HIGH);
}

if(caracter == 'D')
{
 digitalWrite(ch2,LOW);
}
//---------------------------------ch2----------------------
//---------------------------------ch3---------------------
 if(caracter == 'E')
{
 digitalWrite(ch3,HIGH);
}

if(caracter == 'F')
{
 digitalWrite(ch3,LOW);
}
//---------------------------------ch3----------------------
//---------------------------------ch4---------------------
 if(caracter == 'G')
{
 digitalWrite(ch4,HIGH);
}

if(caracter == 'H')
{
 digitalWrite(ch4,LOW);
}
//---------------------------------ch4----------------------
 delay(10);
}
