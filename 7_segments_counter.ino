// Definición de pines para el display de 7 segmentos
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

// Definición de pines para los botones
const int incrementButtonPin = 10;
const int decrementButtonPin = 11;

// Variables para almacenar el valor del contador y el estado de los botones
int contador = 0;
int incrementButtonState;
int decrementButtonState;
int lastIncrementButtonState = HIGH;
int lastDecrementButtonState = HIGH;

// Función para mostrar el número en el display de 7 segmentos
void displayNumber(int number) {
  // Definir los patrones para cada dígito del display
  const byte digitPatterns[] = {
    B11111100,  // 0
    B01100000,  // 1
    B11011010,  // 2
    B11110010,  // 3
    B01100110,  // 4
    B10110110,  // 5
    B10111110,  // 6
    B11100000,  // 7
    B11111110,  // 8
    B11110110   // 9
  };
  
  // Mostrar las unidades en el primer dígito
  digitalWrite(segmentPins[0], bitRead(digitPatterns[number % 10], 0));
  digitalWrite(segmentPins[1], bitRead(digitPatterns[number % 10], 1));
  digitalWrite(segmentPins[2], bitRead(digitPatterns[number % 10], 2));
  digitalWrite(segmentPins[3], bitRead(digitPatterns[number % 10], 3));
  digitalWrite(segmentPins[4], bitRead(digitPatterns[number % 10], 4));
  digitalWrite(segmentPins[5], bitRead(digitPatterns[number % 10], 5));
  digitalWrite(segmentPins[6], bitRead(digitPatterns[number % 10], 6));

  // Mostrar las decenas en el segundo dígito
  digitalWrite(segmentPins[7], bitRead(digitPatterns[number / 10], 0));
  digitalWrite(segmentPins[8], bitRead(digitPatterns[number / 10], 1));
  digitalWrite(segmentPins[9], bitRead(digitPatterns[number / 10], 2));
  digitalWrite(segmentPins[10], bitRead(digitPatterns[number / 10], 3));
  digitalWrite(segmentPins[11], bitRead(digitPatterns[number / 10], 4));
  digitalWrite(segmentPins[12], bitRead(digitPatterns[number / 10], 5));
  digitalWrite(segmentPins[13], bitRead(digitPatterns[number / 10], 6));
}

void setup() {
  // Configurar los pines del display como salidas
  for (int i = 0; i < 14; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Configurar los pines de los botones como entradas
  pinMode(incrementButtonPin, INPUT_PULLUP);
  pinMode(decrementButtonPin, INPUT_PULLUP);
  
  // Inicializar el display con el valor inicial del contador
  displayNumber(contador);
}

void loop() {
  // Leer el estado de los botones
  incrementButtonState = digitalRead(incrementButtonPin);
  decrementButtonState = digitalRead(decrementButtonPin);
  
  // Incrementar el contador si el botón de incremento es presionado
  if (incrementButtonState == LOW && lastIncrementButtonState == HIGH) {
    contador++;
    if (contador > 99) {
      contador = 99;
    }
    displayNumber(contador);
  }
  
  // Decrementar el contador si el botón de decremento es presionado
  if (decrementButtonState == LOW && lastDecrementButtonState == HIGH) {
    contador--;
    if (contador < 0) {
      contador = 0;
    }
    displayNumber(contador);
  }
  
  // Actualizar el estado anterior de los botones
  lastIncrementButtonState = incrementButtonState;
  lastDecrementButtonState = decrementButtonState;
}
