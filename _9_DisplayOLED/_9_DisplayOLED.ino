#include <Wire.h>
#include "SSD1306.h"

#define OLED_RESET 16
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_ADDR 0x3C

SSD1306 display(OLED_ADDR, OLED_SDA, OLED_SCL);

void setup() {
  pinMode(OLED_RESET, OUTPUT);
  delay(50);
  digitalWrite(OLED_RESET, HIGH);
  display.init();
}

void loop() {
  display.clear();
  display.setFont(ArialMT_Plain_16); //24
  display.drawString(15, 20, "Sindormir.net");
  display.display();
  delay(2000);
}


/*

  delay(2000);

  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "CHARLA\nESP32");
  display.display();
  delay(2000);
}*/
