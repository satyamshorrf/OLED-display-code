
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Digital Glitch
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

void setup() {
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  static int line = 0;
  static int frame = 0;

  display.clearDisplay();

  // Header
  display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(3, 3);
  display.print(songTitle);

  // Main lyrics
  display.setTextColor(WHITE);
  display.setCursor(3, 29);
  display.print(lyrics[line]);

  // Glitch duplicate text
  if (random(0, 2)) {
    int shift = random(-3, 4);

    display.setCursor(3 + shift, 29);
    display.print(lyrics[line]);
  }

  // Random digital glitch strips
  for (int i = 0; i < 7; i++) {
    int x = random(0, 120);
    int y = random(16, 55);
    int w = random(3, 22);

    display.drawFastHLine(x, y, w, WHITE);
  }

  // Scan line
  int scanY = 16 + (frame % 39);
  display.drawFastHLine(0, scanY, 128, WHITE);

  // Progress
  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
  display.fillRect(4, 59,
    map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

  display.display();
  delay(90);

  frame++;

  if (frame >= 45) {
    frame = 0;
    line = (line + 1) % totalLines;
  }
}
