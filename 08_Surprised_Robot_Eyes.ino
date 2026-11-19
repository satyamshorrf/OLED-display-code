
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Surprised Eyes
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

  // Large surprised eyes
  display.fillCircle(38, 32, 20, WHITE);
  display.fillCircle(90, 32, 20, WHITE);

  // Small pupils
  display.fillCircle(38, 32, 7, BLACK);
  display.fillCircle(90, 32, 7, BLACK);

  display.display();
  delay(100);
}
