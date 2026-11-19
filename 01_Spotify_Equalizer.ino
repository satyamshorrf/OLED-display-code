
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Spotify Equalizer
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

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
int currentLine = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("SATYAM SHORRF");
  display.setCursor(25, 35);
  display.println("@satyamshorrf");
  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();

  display.fillRoundRect(0, 0, 128, 14, 3, WHITE);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(3, 3);
  display.print(songTitle);

  display.setTextColor(WHITE);
  display.setCursor(3, 20);
  display.println(lyrics[currentLine]);

  for (int i = 0; i < 8; i++) {
    int h = random(3, 22);
    display.fillRoundRect(8 + i * 15, 51 - h, 6, h, 2, WHITE);
  }

  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
  display.fillRect(4, 59, map(currentLine + 1, 0, totalLines, 0, 120), 2, WHITE);

  display.display();
  delay(120);

  static int frame = 0;
  if (++frame >= 40) {
    frame = 0;
    currentLine = (currentLine + 1) % totalLines;
  }
}
