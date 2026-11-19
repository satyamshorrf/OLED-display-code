
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Heartbeat
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

void drawHeart(int cx, int cy, int s) {
  display.fillCircle(cx - s * 3, cy, s * 3, WHITE);
  display.fillCircle(cx + s * 3, cy, s * 3, WHITE);

  display.fillTriangle(
    cx - s * 6, cy,
    cx + s * 6, cy,
    cx, cy + s * 8,
    WHITE
  );
}

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(25, 25);
  display.println("SATYAM SHORRF");
  display.display();
  delay(1500);
}

void loop() {
  static int line = 0;
  static int frame = 0;

  display.clearDisplay();

  display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(3, 3);
  display.print(songTitle);

  display.setTextColor(WHITE);
  display.setCursor(3, 20);
  display.println(lyrics[line]);

  int size = (frame % 12 < 6) ? 2 : 1;

  drawHeart(64, 39, size);

  // Heartbeat pulse line
  display.drawFastHLine(5, 51, 35, WHITE);
  display.drawLine(40, 51, 46, 43, WHITE);
  display.drawLine(46, 43, 52, 56, WHITE);
  display.drawLine(52, 56, 59, 51, WHITE);
  display.drawFastHLine(59, 51, 64, WHITE);

  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
  display.fillRect(4, 59,
    map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

  display.display();
  delay(100);

  if (++frame >= 48) {
    frame = 0;
    line = (line + 1) % totalLines;
  }
}
