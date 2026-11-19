
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Angry Eyes
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

  display.fillRoundRect(20, 20, 36, 32, 7, WHITE);
  display.fillRoundRect(72, 20, 36, 32, 7, WHITE);

  // Angry eyebrows
  display.fillTriangle(
    17, 12, 60, 27, 17, 27, BLACK
  );

  display.fillTriangle(
    111, 12, 68, 27, 111, 27, BLACK
  );

  // Dark pupils
  display.fillCircle(38, 39, 7, BLACK);
  display.fillCircle(90, 39, 7, BLACK);

  display.display();
  delay(100);
}
