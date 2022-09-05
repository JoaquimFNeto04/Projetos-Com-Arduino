// 0 == 48
// 1 == 49 e assim sucessivamente ate 9 == 57

if (Serial.available()) { // Verificar se há caracteres disponíveis
char caractere = Serial.read(); // Armazena caractere lido
if ( isDigit(caractere) ) {  // Verificar se o caractere ASCII é um dígito entre 0 e 9
  piscando = piscando * 100; // Escalando taxa de tempo multiplicando por 100ms
}
