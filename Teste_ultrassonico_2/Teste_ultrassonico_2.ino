/* Ping))) Sensor

   This sketch reads a PING))) ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse
   to return.  The length of the returning pulse is proportional to
   the distance of the object from the sensor.

   The circuit:
      +V connection of the PING))) attached to +5V
      GND connection of the PING))) attached to ground
      SIG connection of the PING))) attached to digital pin 7

   http://www.arduino.cc/en/Tutorial/Ping

   created 3 Nov 2008
   by David A. Mellis
   modified 30 Aug 2011
   by Tom Igoe

   This example code is in the public domain.

*/

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingTrigger = 8;
const int Sensor_1 = 7;
const int Sensor_2 = 6;

float metros = 0;
float metros2 = 0;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;

// const int Sensor_3 = 5;

void setup() {

  pinMode(pingTrigger, OUTPUT);
  pinMode(Sensor_1, INPUT);
  pinMode(Sensor_2, INPUT);
  //pinMode(Sensor_3, INPUT);



  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  //delay(1000);

  Serial.println(" ");
  Serial.println(" ");

  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  float duration, inches, cm;

  // SENSOR 1
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(Sensor_1, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.println("Sensor 1");
  //Serial.print(inches);
  //Serial.print("in, ")
  metros = cm / 100;
  Serial.print(metros);
  Serial.print(" M");
  Serial.println();

  //delay(100);

  // SENSOR 2
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingTrigger, LOW);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrigger, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(Sensor_2, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.println("Sensor 2");
  //Serial.print(inches);
  //Serial.print("in, ");

  metros2 = cm / 100;

  Serial.print(metros2);
  Serial.print(" M");
  Serial.println();

  //delay(100);

  if (((metros < 3.50) or (metros > 5)) and ((metros2 < 3.50) or (metros2 > 5))) {
    a++;
    d++;
   
  }
  else {
    digitalWrite (13, LOW);
    b++;
        
  }

  if (d == 3){
    digitalWrite (13, HIGH);
    
    delay(2000);
   e++;
   d = 0; 
  }

    c++;
  
 
    Serial.print("TOTAL DE ACIONAMENTOS GERAL: ");
    Serial.println(a);
    Serial.print("TOTAL DE TRAVAMENTO: ");
    Serial.println(e);
    Serial.print("TOTAL DE NAO ACIONAMENTOS: ");
    Serial.println(b);
    Serial.print("TOTAL DE LEITURAS : ");
    Serial.println(c);



  /*/ SENSOR 3
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(pingTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pingTrigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingTrigger, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    duration = pulseIn(Sensor_3, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
    Serial.println("Sensor 3");
    //Serial.print(inches);
    //Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();

    delay(1000);*/
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
