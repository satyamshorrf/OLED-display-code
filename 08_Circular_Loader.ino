
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Circular Music Loader
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

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

int angle = 0;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);
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

  int cx = 64;
  int cy = 43;

  // Circular rings
  display.drawCircle(cx, cy, 8, WHITE);
  display.drawCircle(cx, cy, 15, WHITE);

  // Rotating indicator
  float rad = angle * 0.0174533;

  int x = cx + cos(rad) * 15;
  int y = cy + sin(rad) * 15;

  display.fillCircle(x, y, 3, WHITE);
  display.fillCircle(cx, cy, 2, WHITE);

  // Small rotating dots
  for (int i = 0; i < 3; i++) {
    float a = (angle + i * 120) * 0.0174533;

    int dx = cx + cos(a) * 22;
    int dy = cy + sin(a) * 18;

    display.drawPixel(dx, dy, WHITE);
  }

  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
  display.fillRect(4, 59,
    map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

  display.display();

  angle = (angle + 12) % 360;
  delay(70);

  if (++frame >= 50) {
    frame = 0;
    line = (line + 1) % totalLines;
  }
}
