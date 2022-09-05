#define sensor_boia_1 A0
#define sensor_boia_2 A1

int controle;

int sensor1;
int sensor2;
void setup() {
  // put your setup code here, to run once:
pinMode(sensor_boia_1,INPUT_PULLUP);
pinMode(sensor_boia_2,INPUT_PULLUP);

Serial.begin(9600);

Serial.println("LEITOR DE CAIXA D'AGUA");
Serial.println("CARREGANDO");
delay(1000);

}

void loop() {
  
delay(2000);

// faz as leituras maxima e minima das boias:
  int leitura_sens_Max=analogRead(sensor_boia_1);
  int leitura_sens_Min=analogRead(sensor_boia_2);
  //////////////////////////////////////////////////////////////////////////////////////////////////
  if(leitura_sens_Max<50){
    sensor1=1;
  }else{
    sensor1=0;
  }
  if(leitura_sens_Min<50){
    sensor2=1;
  }else{
    sensor2=0;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
  if((sensor1==0)and(sensor2==0)){
    //tanque cheio
    Serial.println( "A CAIXA D'AGUA ESTÁ CHEIA.");
  }

  if((sensor1==0)and(sensor2==1)){
    //erro
    Serial.println( "PROBLEMA EM UM DOS SENSORES");
    Serial.println( "LIGUE PARA ASSISTENCIA (83)3033-3391 ");
    
  }

  if((sensor1==1)and(sensor2==0)){
    //leitura media
    Serial.println( "A CAIXA D'AGUA ESTÁ EM UM NIVEL INTERMEDIARIO.");
  }

  if((sensor1==1)and(sensor2==1)){
    //vazio
    Serial.println( "A CAIXA D'AGUA ESTÁ EM UM NIVEL CRITICO.");
  }
  
  //Serial.println(leitura_sens_Max);  
}
