
#define caixa_boia_1 2
#define caixa_boia_2 3
#define caixa_boia_3 4
#define cheio 5
#define medio 6
#define baixo 7
#define critico 8
#define bip 9
#define botao 10
#define bomba 11

bool alarme = 0;
bool statusbomba = 0;
int controlebomba = 0;

void setup() {

  Serial.begin(9600);

  pinMode(caixa_boia_1, INPUT_PULLUP);
  pinMode(caixa_boia_2, INPUT_PULLUP);
  pinMode(caixa_boia_3, INPUT_PULLUP);
  pinMode(botao, INPUT_PULLUP);
  pinMode(cheio, OUTPUT);
  pinMode(medio, OUTPUT);
  pinMode(baixo, OUTPUT);
  pinMode(critico, OUTPUT);
  pinMode(bip, OUTPUT);
  pinMode(bomba, OUTPUT);

  carregando();
}

void loop() {

  delay(1000);

  int statusbotao = digitalRead(botao);

  if (statusbotao == 0) {
    alarme = !alarme;
  }

  if (statusbomba == 1) {
    digitalWrite (bomba, LOW); // LIGA A BOMBA
  }
  if (statusbomba != 1) {
    digitalWrite (bomba, HIGH); // DESLIGA A BOMBA
  }

  delay(100);

  Serial.print ("ALARME = ");
  Serial.println (alarme);
  Serial.print("CONTROLE BOMBA: ");
  Serial.println (controlebomba);

  LeituraCaixa();

}

void LeituraCaixa() {

  int nivel = 0;

  if (digitalRead(caixa_boia_1)) nivel++;
  if (digitalRead(caixa_boia_2)) nivel++;
  if (digitalRead(caixa_boia_3)) nivel++;

  Serial.print (" NIVEL = ");
  Serial.println (nivel);

  if (nivel == 0) {

    nivelcritico();

  }

  if (nivel == 1) {

    nivelbaixo();

  }

  if (nivel == 2) {

    Serial.println("A CAIXA ESTA COM O  NIVEL  MEDIO");
    digitalWrite(cheio, LOW);
    digitalWrite(medio, HIGH);
    digitalWrite(baixo, HIGH);
    digitalWrite(critico, HIGH);
    delay (1000);
    alarme = 0;

  }

  if (nivel == 3) {

    if ((controlebomba == 40) and (statusbomba == 1)) {
      controlebomba = 0;
      statusbomba = 0;
    }

    if ((controlebomba < 40) and (statusbomba == 1)) {
      controlebomba++;
    }

    alarme = 0;
    Serial.println("A CAIXA ESTA COM O  NIVEL  CHEIO ");
    digitalWrite(cheio, HIGH);
    digitalWrite(medio, HIGH);
    digitalWrite(baixo, HIGH);
    digitalWrite(critico, HIGH);
    delay (1000);
  }
}

void carregando() {

  Serial.print("O SISTEMA ESTA CARREGANDO");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, LOW);
  digitalWrite(critico, LOW);
  delay(300);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, LOW);
  digitalWrite(critico, HIGH);
  delay(300);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);
  delay(300);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, HIGH);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);
  delay(300);
  Serial.print(".");
  digitalWrite(cheio, HIGH);
  digitalWrite(medio, HIGH);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);
  delay(200);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, HIGH);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);
  delay(200);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);
  delay(200);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, LOW);
  digitalWrite(critico, HIGH);
  delay(200);
  Serial.print(".");
  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, LOW);
  digitalWrite(critico, LOW);
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(200);
  Serial.println("");

}

void nivelcritico() {
  statusbomba = 1;
  Serial.println("A CAIXA ESTA COM O NIVEL CRITICO");

  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, LOW);

  if (alarme == 1) {
    digitalWrite(critico, HIGH);
  }

  if (alarme == 0) {
    digitalWrite(bip, HIGH);
    digitalWrite(critico, HIGH);
    delay(300);
    digitalWrite(bip, LOW);
    digitalWrite(critico, LOW);
    delay(300);
    digitalWrite(bip, HIGH);
    digitalWrite(critico, HIGH);
    delay(300);
    digitalWrite(bip, LOW);
    digitalWrite(critico, LOW);
    delay(300);
    digitalWrite(bip, HIGH);
    digitalWrite(critico, HIGH);
    delay(300);
    digitalWrite(bip, LOW);
    digitalWrite(critico, LOW);
  }
}

void nivelbaixo() {
  statusbomba = 1;
  Serial.println("A CAIXA ESTA COM O  NIVEL  BAIXO");

  digitalWrite(cheio, LOW);
  digitalWrite(medio, LOW);
  digitalWrite(baixo, HIGH);
  digitalWrite(critico, HIGH);

  if (alarme == 0) {
    digitalWrite(bip, HIGH);
    delay(600);
    digitalWrite(bip, LOW);
    delay(600);
    digitalWrite(bip, HIGH);
    delay(600);
    digitalWrite(bip, LOW);
    delay(600);
    digitalWrite(bip, HIGH);
    delay(600);
    digitalWrite(bip, LOW);
  }
}
