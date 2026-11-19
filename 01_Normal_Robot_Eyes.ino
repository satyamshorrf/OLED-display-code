
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Normal Eyes
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  display.clearDisplay();

  // Left eye
  display.fillRoundRect(20, 14, 36, 38, 9, WHITE);

  // Right eye
  display.fillRoundRect(72, 14, 36, 38, 9, WHITE);

  display.display();
  delay(100);
}
