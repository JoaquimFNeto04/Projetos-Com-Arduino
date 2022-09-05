/*Pinagem do arduino*/
 
//motor_A
int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;
 
//motor_B
int IN3 = 6 ;
int IN4 = 7 ;
int velocidadeB = 5;
 
//variavel auxiliar
int velocidade = 0;
 
//Inicializa Pinos
void setup(){
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
}
 
void loop(){
 
/*Exemplo de velocidades no motor A*/
 
//Sentido 2
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
//Baixa
analogWrite(velocidadeB,65);

}
