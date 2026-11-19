
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Looking Right
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

  display.fillRoundRect(20, 14, 36, 38, 9, WHITE);
  display.fillRoundRect(72, 14, 36, 38, 9, WHITE);

  // Right pupils
  display.fillRoundRect(40, 25, 15, 19, 6, BLACK);
  display.fillRoundRect(92, 25, 15, 19, 6, BLACK);

  display.display();
  delay(100);
}
