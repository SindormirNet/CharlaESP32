#define LED BUILTIN_LED
#define UMBRAL_L 20
#define UMBRAL_H 45

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  delay(1000);
  Serial.println("ESP32 Hall Test");
}

void loop() {
  int lectura =  hallRead();
  Serial.println(lectura);
  if (lectura > UMBRAL_H || lectura < UMBRAL_L){
    digitalWrite(LED, HIGH);
    delay(1000);
  }
  else{
    digitalWrite(LED, LOW);
  }
  delay(20);
}
