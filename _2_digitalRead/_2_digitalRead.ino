#define LED 16 //2 en la placa Lora
#define BOTON 0

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT);
}

void loop() {
  if (digitalRead(BOTON) == HIGH) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
