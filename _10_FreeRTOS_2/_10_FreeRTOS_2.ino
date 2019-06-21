#define PULSADOR 0

void tarea1(void * pvParameters) {
  while (true) {
    digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
    delay(1000);
  }
}
void tarea2(void * pvParameters) {
  unsigned int veces = 0;
  while (true) {
    if (digitalRead(PULSADOR) == LOW) { //Lógica inversa
      Serial.print("Me han pulsado: ");
      Serial.println(veces++);
      delay(150);
    }
  }
}

void setup() {
  Serial.begin(112500);
  delay(1000);
  pinMode(BUILTIN_LED, OUTPUT);
  xTaskCreate(tarea1,"parpadeo", 10000, NULL, 0, NULL); 
  xTaskCreate(tarea2,"pulsador", 10000, NULL, 0, NULL);
}

void loop() {
  Serial.println("Iniciando loop()");
  while (true) {
    delay(1000);
  }
}



