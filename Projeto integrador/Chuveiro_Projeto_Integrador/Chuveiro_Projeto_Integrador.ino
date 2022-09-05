#include <NewPing.h>

// INICIO DA DECLARAÇÃO DAS VARIAVEIS.
int solenoide = 2;
int chave = 3;
int buzzer = 4;  
int vermelho = 5;
int amarelo = 6;
int verde = 7;
// FIM DA DECLARAÇÃO DAS VARIAVEIS.
/* Aqui nós conectar os pinos onde o sensor está configurado */

#define TRIGGER_PIN  1
#define ECHO_PIN     0
#define MAX_DISTANCE 400

 
/* Criar o objeto de classe NewPing */
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  
  Serial.begin(9600);
// DEFINE OS PINOS COMO ENTRADA OU SAIDA
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(solenoide, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(chave, INPUT);
 
}
 
void loop() {
  
  // Esperar 1 segundo entre medições
  
  delay(800);
  
  // Obter medição do tempo de viagem do som e salvar na variável uS.
  int uS = sonar.ping_median();
  int boia = digitalRead(botao);
  // Imprimir a distância medida ao console serial
  
  Serial.print("Distancia: ");
  
  // Calcular la distancia con base en una constante
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");

/* SE A DISTANCIA FOR DIFERENTE DE 0 ACIONA O CHUVEIRO */     
   if (uS / US_ROUNDTRIP_CM != 0) {
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(azul, LOW);
  }

  if ((uS / US_ROUNDTRIP_CM <= 20) && (uS / US_ROUNDTRIP_CM > 010) && (boia == LOW)) {
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(azul, HIGH);
  }
  else if ((uS / US_ROUNDTRIP_CM <= 20) && (uS / US_ROUNDTRIP_CM > 010) && (boia == HIGH)) {
    
    digitalWrite(vermelho, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(azul, LOW);

  }

  if ((uS / US_ROUNDTRIP_CM > 20) && (boia == LOW)) {
  
    digitalWrite(vermelho, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(azul, HIGH);
     }
      
      else if ((uS / US_ROUNDTRIP_CM > 20) && (boia == HIGH)) {
  
    digitalWrite(vermelho, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(azul, LOW);
     }   
  if (boia == LOW) {
    
    digitalWrite(vermelho_2, LOW);
    digitalWrite(verde_2, HIGH);
    digitalWrite(amarelo_2, LOW);
             
  }
  
  if (boia == HIGH) {
    
    digitalWrite(vermelho_2, HIGH);
    digitalWrite(verde_2, LOW);
    digitalWrite(amarelo_2, LOW);
             
  }
}

