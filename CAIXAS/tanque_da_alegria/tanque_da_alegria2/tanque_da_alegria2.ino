#define sensor_boia_1 A7
#define sensor_boia_2 A6
#define bomba 2

int controle;

int sensor1;
int sensor2;
void setup() {
  // put your setup code here, to run once:
pinMode(sensor_boia_1,INPUT_PULLUP);
pinMode(sensor_boia_2,INPUT_PULLUP);
pinMode(bomba, OUTPUT);
Serial.begin(9600);

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
    sensor1=0;
  }else{
    sensor1=1;
  }
  if(leitura_sens_Min<100){
    sensor2=0;
  }else{
    sensor2=1;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
  if((sensor1==0)and(sensor2==0)){
    //tanque cheio
    Serial.println( "A CAIXA D'AGUA ESTA CHEIA.");
    digitalWrite(bomba, LOW);
  }

  if((sensor1==0)and(sensor2==1)){
    //erro
    Serial.println( "PROBLEMA EM UM DOS SENSORES");
    Serial.println( "LIGUE PARA ASSISTENCIA (83)3033-3391 ");
    digitalWrite(bomba, LOW);    
  }

  if((sensor1==1)and(sensor2==0)){
    //leitura media
    Serial.println( "A CAIXA D'AGUA ESTA EM UM NIVEL INTERMEDIARIO.");
  }

  if((sensor1==1)and(sensor2==1)){
    //vazio
    Serial.println( "A CAIXA D'AGUA ESTA EM UM NIVEL CRITICO.");
    digitalWrite(bomba, HIGH);
  }
  
  Serial.println(" ");  
  //Serial.print("Sensor maximo e ");
  //Serial.print(leitura_sens_Max);
  //Serial.print(" e Sensor minimo e ");
  //Serial.print(leitura_sens_Min);
  Serial.print(" O valor do sensor1 e ");  
  Serial.print(sensor1);
  Serial.print(" E valor do sensor2 e ");  
  Serial.println(sensor2);  
  Serial.println(" ");
}
