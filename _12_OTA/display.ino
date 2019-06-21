
void display_setup() {
  pinMode(OLED_RESET, OUTPUT);
  delay(50);
  digitalWrite(OLED_RESET, HIGH);
  display.init();
}



void display_show() {
  unsigned long t=0;
  static byte contador;

  if (millis() - t > 1000) {
    t = millis();

    display.clear();
    display.setFont(ArialMT_Plain_16); //24
    display.drawString(15, 20, "Sindormir.net");
    display.drawString(30, 40, String(contador++));
    display.display();
    delay(2000);
  }
}

