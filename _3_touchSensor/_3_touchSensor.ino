#define TOUCH T4
#define LED BUILTIN_LED
#define UMBRAL 80

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  delay(1000);
  Serial.println("ESP32 Touch Test");
}

void loop() {
  int lectura = touchRead(TOUCH);
  Serial.println(lectura);

  if (lectura < UMBRAL) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  delay(20);
}

