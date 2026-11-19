
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Blinking Eyes
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void drawEyes(int h) {
  display.clearDisplay();

  int y = 14 + (38 - h) / 2;

  display.fillRoundRect(20, y, 36, h, 8, WHITE);
  display.fillRoundRect(72, y, 36, h, 8, WHITE);

  display.display();
}

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  drawEyes(38);
  delay(1800);

  // Close eyes
  for (int h = 38; h >= 2; h -= 6) {
    drawEyes(h);
    delay(20);
  }

  drawEyes(2);
  delay(100);

  // Open eyes
  for (int h = 2; h <= 38; h += 6) {
    drawEyes(h);
    delay(20);
  }

  drawEyes(38);
  delay(1500);
}
