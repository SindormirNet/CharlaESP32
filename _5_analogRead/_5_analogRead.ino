#define ANALOG 36

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  int lectura analogRead(ANALOG);
  Serial.println(lectura);
  delay(20);
}


