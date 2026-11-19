
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Pixel Reveal
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const char* songTitle = "Jo Tum Mere Ho";

const char* lyrics[] = {
  "Jo tum mere ho...",
  "Toh main kuch nahi",
  "Maangunga...",
  "Jo tum mere ho...",
  "Toh main sun lunga",
  "Baatein saari..."
};

const int totalLines = sizeof(lyrics) / sizeof(lyrics[0]);

#define PIXEL_COUNT 45

int pixelX[PIXEL_COUNT];
int pixelY[PIXEL_COUNT];

void setup() {
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  for (int line = 0; line < totalLines; line++) {

    // Generate random pixel positions
    for (int i = 0; i < PIXEL_COUNT; i++) {
      pixelX[i] = random(0, 128);
      pixelY[i] = random(18, 54);
    }

    for (int frame = 0; frame <= PIXEL_COUNT; frame++) {
      display.clearDisplay();

      display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
      display.setTextColor(BLACK);
      display.setTextSize(1);
      display.setCursor(3, 3);
      display.print(songTitle);

      // Original text underneath
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setCursor(3, 30);
      display.print(lyrics[line]);

      // Reveal pattern
      for (int i = 0; i < frame; i++) {
        display.drawPixel(pixelX[i], pixelY[i], WHITE);
      }

      display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
      display.fillRect(4, 59,
        map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

      display.display();
      delay(35);
    }

    delay(600);
  }
}
