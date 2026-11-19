
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Smooth Scrolling Lyrics
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

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(25, 25);
  display.println("SATYAM SHORRF");
  display.display();
  delay(2000);
}

void loop() {
  for (int line = 0; line < totalLines; line++) {
    int len = strlen(lyrics[line]);
    int width = len * 6;

    for (int x = 128; x > -width; x--) {
      display.clearDisplay();

      display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
      display.setTextColor(BLACK);
      display.setTextSize(1);
      display.setCursor(3, 3);
      display.print(songTitle);

      display.setTextColor(WHITE);
      display.setCursor(x, 30);
      display.print(lyrics[line]);

      display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
      display.fillRect(4, 59, map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

      display.display();
      delay(20);
    }
    delay(400);
  }
}
