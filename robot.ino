/*
 * Project: 0.96" OLED Robot Eyes Animation
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

// Aankhon ki default position aur size
int leftEyeX = 22;
int rightEyeX = 74;
int eyeY = 14;
int eyeWidth = 32;
int eyeHeight = 36;
int cornerRadius = 8;

void setup() {
  Serial.begin(9600);

  // Agar 0x3C par display na chale toh 0x3D try karein
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED nahi mila! Wiring check karein."));
    for (;;);
  }

  display.clearDisplay();
  display.display();
}

// Normal aankhein draw karne ka function
void drawEyes(int offsetX, int offsetY, int h) {
  display.clearDisplay();
  int yPos = eyeY + (eyeHeight - h) / 2 + offsetY;
  display.fillRoundRect(leftEyeX + offsetX, yPos, eyeWidth, h, cornerRadius, SSD1306_WHITE);
  display.fillRoundRect(rightEyeX + offsetX, yPos, eyeWidth, h, cornerRadius, SSD1306_WHITE);
  display.display();
}

// Aankh jhapkane (Blink) ka animation
void blinkEyes() {
  for (int h = eyeHeight; h >= 4; h -= 8) {
    drawEyes(0, 0, h);
    delay(15);
  }
  for (int h = 4; h <= eyeHeight; h += 8) {
    drawEyes(0, 0, h);
    delay(15);
  }
}

// Khush (Happy ^ ^) aankhein
void happyEyes() {
  display.clearDisplay();
  display.fillRoundRect(leftEyeX, 20, eyeWidth, 24, 10, SSD1306_WHITE);
  display.fillRoundRect(rightEyeX, 20, eyeWidth, 24, 10, SSD1306_WHITE);
  // Neeche ka hissa kaat kar ^ ^ shape banana
  display.fillCircle(leftEyeX + eyeWidth / 2, 46, 18, SSD1306_BLACK);
  display.fillCircle(rightEyeX + eyeWidth / 2, 46, 18, SSD1306_BLACK);
  display.display();
}

void loop() {
  // 1. Seedha dekhna aur blink karna
  drawEyes(0, 0, eyeHeight);
  delay(1500);
  blinkEyes();
  delay(800);

  // 2. Left side dekhna
  drawEyes(-10, 0, eyeHeight);
  delay(1000);

  // 3. Right side dekhna
  drawEyes(10, 0, eyeHeight);
  delay(1000);

  // 4. Center mein aana aur double blink
  drawEyes(0, 0, eyeHeight);
  delay(500);
  blinkEyes();
  delay(150);
  blinkEyes();
  delay(800);

  // 5. Happy expression (^ ^)
  happyEyes();
  delay(2000);
}
