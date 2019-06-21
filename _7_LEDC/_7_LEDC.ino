#define LED 16 //17
#define FREQ 5000
#define CHANNEL 0
#define RES 16

void setup() {
  ledcSetup(CHANNEL, FREQ, RES);
  ledcAttachPin(LED, CHANNEL);
}
void loop() {
  for (int brillo = 0; brillo <= 65535; brillo++) {
    ledcWrite(CHANNEL, brillo);
    delayMicroseconds(20);
  }
  for (int brillo = 65535; brillo >= 0; brillo--) {
    ledcWrite(CHANNEL, brillo);
    delayMicroseconds(20);
  }
}

