
/*
 * Project: OLED Robot Emoji Animation
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }
}

void loop() {
  for (int i = 0; i < 15; i++) {
    showEmoji(i);
    delay(1200);
  }
}

void showEmoji(int type) {
  display.clearDisplay();

  int x = 64, y = 30;

  // Face
  display.drawCircle(x, y, 25, WHITE);

  switch (type) {

    case 0: // Happy
      eyes();
      display.drawLine(52, 39, 58, 44, WHITE);
      display.drawLine(58, 44, 70, 44, WHITE);
      display.drawLine(70, 44, 76, 39, WHITE);
      break;

    case 1: // Love
      heart(51, 27);
      heart(77, 27);
      display.drawLine(54, 43, 74, 43, WHITE);
      break;

    case 2: // Cool
      display.fillRoundRect(40, 22, 22, 12, 3, WHITE);
      display.fillRoundRect(66, 22, 22, 12, 3, WHITE);
      display.drawLine(62, 27, 66, 27, WHITE);
      display.drawLine(55, 43, 73, 43, WHITE);
      break;

    case 3: // Sad
      display.fillCircle(52, 26, 3, WHITE);
      display.fillCircle(76, 26, 3, WHITE);
      display.drawCircle(64, 53, 10, WHITE);
      display.drawLine(54, 53, 74, 53, WHITE);
      break;

    case 4: // Surprised
      display.drawCircle(52, 26, 6, WHITE);
      display.drawCircle(76, 26, 6, WHITE);
      display.drawCircle(64, 43, 6, WHITE);
      break;

    case 5: // Angry
      display.drawLine(43, 19, 59, 26, WHITE);
      display.drawLine(69, 26, 85, 19, WHITE);
      display.fillCircle(52, 30, 4, WHITE);
      display.fillCircle(76, 30, 4, WHITE);
      display.drawLine(52, 48, 76, 48, WHITE);
      break;

    case 6: // Sleepy
      display.drawLine(45, 28, 59, 28, WHITE);
      display.drawLine(69, 28, 83, 28, WHITE);
      display.drawLine(55, 45, 73, 45, WHITE);
      display.setTextSize(1);
      display.setCursor(94, 5);
      display.print("Zz");
      break;

    case 7: // Wink
      display.fillCircle(52, 27, 4, WHITE);
      display.drawLine(70, 27, 84, 27, WHITE);
      smile();
      break;

    case 8: // Confused
      display.drawCircle(52, 27, 4, WHITE);
      display.fillCircle(76, 27, 4, WHITE);
      display.drawLine(58, 45, 72, 42, WHITE);
      break;

    case 9: // Crying
      eyes();
      display.fillCircle(53, 37, 3, WHITE);
      display.fillCircle(76, 37, 3, WHITE);
      display.fillCircle(52, 46, 2, WHITE);
      display.fillCircle(76, 46, 2, WHITE);
      break;

    case 10: // Laughing
      display.fillCircle(52, 27, 4, WHITE);
      display.fillCircle(76, 27, 4, WHITE);
      display.fillRoundRect(52, 38, 24, 12, 5, WHITE);
      break;

    case 11: // Shy
      eyes();
      display.drawLine(57, 44, 64, 47, WHITE);
      display.drawLine(64, 47, 71, 44, WHITE);
      display.drawCircle(42, 39, 4, WHITE);
      display.drawCircle(86, 39, 4, WHITE);
      break;

    case 12: // Dizzy
      spiral(52, 27);
      spiral(76, 27);
      display.drawLine(56, 45, 72, 45, WHITE);
      break;

    case 13: // Excited
      display.drawCircle(52, 27, 7, WHITE);
      display.drawCircle(76, 27, 7, WHITE);
      display.drawCircle(64, 43, 8, WHITE);
      break;

    case 14: // Robot
      display.drawRoundRect(43, 19, 42, 24, 4, WHITE);
      display.fillCircle(54, 30, 4, WHITE);
      display.fillCircle(74, 30, 4, WHITE);
      display.drawLine(54, 49, 74, 49, WHITE);
      break;
  }

  display.display();
}

void eyes() {
  display.fillCircle(52, 27, 4, WHITE);
  display.fillCircle(76, 27, 4, WHITE);
}

void smile() {
  display.drawLine(54, 42, 64, 47, WHITE);
  display.drawLine(64, 47, 74, 42, WHITE);
}

void heart(int x, int y) {
  display.fillCircle(x-4, y, 5, WHITE);
  display.fillCircle(x+4, y, 5, WHITE);
  display.fillTriangle(x-9, y+2, x+9, y+2, x, y+12, WHITE);
}

void spiral(int x, int y) {
  display.drawCircle(x, y, 7, WHITE);
  display.drawCircle(x+2, y, 3, WHITE);
}
