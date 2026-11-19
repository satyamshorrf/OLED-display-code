
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Bouncing Ball
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
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
}

void loop() {
  static int frame = 0;
  static int line = 0;

  display.clearDisplay();

  display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(3, 3);
  display.print(songTitle);

  display.setTextColor(WHITE);
  display.setCursor(3, 20);
  display.println(lyrics[line]);

  int x = 5 + (frame % 60) * 2;
  int phase = frame % 30;
  int y = 52 - abs(phase - 15) * 2;

  display.drawFastHLine(0, 55, 128, WHITE);
  display.fillCircle(x, y, 4, WHITE);

  display.display();
  delay(45);

  frame++;

  if (frame >= 60) {
    frame = 0;
    line = (line + 1) % totalLines;
  }
}
