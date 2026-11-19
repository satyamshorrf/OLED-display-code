/*
 * Project: 0.96" OLED Song Lyrics Display
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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* lyrics[] = {
  "Tera fitoor...",
  "Jab se chadh gaya re",
  "Ishq jo zara sa tha",
  "Woh badh gaya re...",
  "Tera fitoor...",a
  "Jab se chadh gaya re"
};

const int lineDelay[] = {2200, 2800, 2500, 3000, 2200, 3000};
const int totalLines = sizeof(lyrics) / sizeof(lyrics[0]);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED nahi mila"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  for (int i = 0; i < totalLines; i++) {
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(18, 2);
    display.print("~ NOW PLAYING ~");
    display.drawLine(0, 13, 128, 13, SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(0, 24);
    display.println(lyrics[i]);

    display.display();
    delay(lineDelay[i]);
  }

  delay(2000);
}
