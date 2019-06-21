#define DAC_PIN 25

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < 256; i ++) {
    dacWrite(DAC_PIN, i);
    delay(10);
  }

  /* for (int deg = 0; deg < 360; deg = deg + 8){
    dacWrite(DAC_PIN, int(128 + 80 * (sin(deg*PI/180)+sin(3*deg*PI/180)/3+sin(5*deg*PI/180)/5+sin(7*deg*PI/180)/7+sin(9*deg*PI/180)/9+sin(11*deg*PI/180)/11)));
  }*/

  /*for (int deg = 0; deg < 360; deg++) {
    dacWrite(DAC_PIN, int(128 + 127 * (sin(deg * PI / 180))));
  }*/
  
}
