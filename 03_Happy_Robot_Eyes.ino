
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Happy Eyes
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

  // Happy curved eyes
  display.fillRoundRect(20, 17, 36, 29, 12, WHITE);
  display.fillRoundRect(72, 17, 36, 29, 12, WHITE);

  // Cut lower area to make smiling arcs
  display.fillCircle(38, 49, 19, BLACK);
  display.fillCircle(90, 49, 19, BLACK);

  display.display();
  delay(100);
}
