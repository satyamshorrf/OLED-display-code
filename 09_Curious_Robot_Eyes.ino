
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Curious Eyes
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void drawCurious(int offset) {
  display.clearDisplay();

  display.fillRoundRect(20, 14, 36, 38, 9, WHITE);
  display.fillRoundRect(72, 14, 36, 38, 9, WHITE);

  // Pupils looking upward
  display.fillCircle(38, 20 + offset, 7, BLACK);
  display.fillCircle(90, 20 + offset, 7, BLACK);

  display.display();
}

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  // Curious upward eye movement
  for (int i = 0; i <= 6; i++) {
    drawCurious(6 - i);
    delay(80);
  }

  delay(900);

  for (int i = 0; i <= 6; i++) {
    drawCurious(i);
    delay(80);
  }

  delay(500);
}
