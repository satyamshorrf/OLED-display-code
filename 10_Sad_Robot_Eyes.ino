
/*
 * Project: 0.96" OLED Robot Eyes Animation
 * Animation: Sad Eyes with Tears
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void drawSad(int tearY) {
  display.clearDisplay();

  // Sad eye shapes
  display.fillRoundRect(20, 19, 36, 30, 9, WHITE);
  display.fillRoundRect(72, 19, 36, 30, 9, WHITE);

  // Sad eyebrows
  display.drawLine(20, 12, 45, 17, WHITE);
  display.drawLine(83, 17, 108, 12, WHITE);

  // Pupils
  display.fillCircle(38, 37, 6, BLACK);
  display.fillCircle(90, 37, 6, BLACK);

  // Falling tears
  display.fillCircle(30, tearY, 3, WHITE);
  display.fillCircle(98, tearY - 5, 3, WHITE);

  display.fillTriangle(
    27, tearY - 2,
    33, tearY - 2,
    30, tearY - 8,
    WHITE
  );

  display.fillTriangle(
    95, tearY - 7,
    101, tearY - 7,
    98, tearY - 13,
    WHITE
  );

  display.display();
}

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  // Tears continuously fall
  for (int y = 35; y <= 64; y += 2) {
    drawSad(y);
    delay(100);
  }

  delay(300);
}
