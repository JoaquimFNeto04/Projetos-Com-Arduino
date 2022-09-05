//Programa : Controle 2 motores DC usando Ponte H L298N
//Autor : FILIPEFLOP

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

int IN11 = 8;
int IN22 = 9;
int IN33 = 10;
int IN44 = 11;

void setup()
{
  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IN11, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN33, OUTPUT);
  pinMode(IN44, OUTPUT);
}

void loop()
{
  //Gira o Motor A no sentido horario
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, LOW);

  delay(10000);

  //Para o motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, HIGH);

  delay(3000);


  //Gira o Motor A no sentido anti-horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, HIGH);

  delay(10000);
  
  //Para o motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, HIGH);
  
  delay(3000);

}
