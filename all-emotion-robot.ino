
/*
 * Project: 0.96" OLED Robot Eyes - 10 Animations
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

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET
);

const int EYE_W = 38;
const int EYE_H = 38;
const int LEFT_X = 20;
const int RIGHT_X = 70;
const int EYE_Y = 13;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  normalEyes();
  blinkEyes();
  happyEyes();
  lookLeft();
  lookRight();
  sleepyEyes();
  angryEyes();
  surprisedEyes();
  curiousEyes();
  sadEyes();
}

// 1. NORMAL EYES
void normalEyes() {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, EYE_Y, EYE_W, EYE_H, 9, WHITE);
  display.fillRoundRect(RIGHT_X, EYE_Y, EYE_W, EYE_H, 9, WHITE);

  display.display();
  delay(1800);
}

// 2. BLINKING EYES
void blinkEyes() {
  for (int h = EYE_H; h >= 2; h -= 4) {
    drawEyes(h);
    delay(35);
  }

  delay(150);

  for (int h = 2; h <= EYE_H; h += 4) {
    drawEyes(h);
    delay(35);
  }

  delay(500);
}

// 3. HAPPY EYES
void happyEyes() {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, 19, EYE_W, 30, 12, WHITE);
  display.fillRoundRect(RIGHT_X, 19, EYE_W, 30, 12, WHITE);

  display.fillCircle(LEFT_X + 19, 12, 17, BLACK);
  display.fillCircle(RIGHT_X + 19, 12, 17, BLACK);

  display.display();
  delay(1800);
}

// 4. LOOK LEFT
void lookLeft() {
  drawPupils(-9, 0);
  delay(1500);
}

// 5. LOOK RIGHT
void lookRight() {
  drawPupils(9, 0);
  delay(1500);
}

// 6. SLEEPY EYES
void sleepyEyes() {
  for (int h = 38; h >= 8; h -= 2) {
    drawEyes(h);
    delay(100);
  }

  delay(1200);

  for (int h = 8; h <= 38; h += 2) {
    drawEyes(h);
    delay(100);
  }

  delay(500);
}

// 7. ANGRY EYES
void angryEyes() {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, 18, EYE_W, 34, 8, WHITE);
  display.fillRoundRect(RIGHT_X, 18, EYE_W, 34, 8, WHITE);

  display.fillTriangle(LEFT_X, 10, LEFT_X + 38, 22,
                       LEFT_X + 38, 10, BLACK);

  display.fillTriangle(RIGHT_X, 22, RIGHT_X + 38, 10,
                       RIGHT_X + 38, 10, BLACK);

  display.fillCircle(LEFT_X + 19, 37, 8, BLACK);
  display.fillCircle(RIGHT_X + 19, 37, 8, BLACK);

  display.display();
  delay(1800);
}

// 8. SURPRISED EYES
void surprisedEyes() {
  display.clearDisplay();

  display.fillCircle(39, 32, 19, WHITE);
  display.fillCircle(89, 32, 19, WHITE);

  display.fillCircle(39, 32, 7, BLACK);
  display.fillCircle(89, 32, 7, BLACK);

  display.display();
  delay(1800);
}

// 9. CURIOUS EYES
void curiousEyes() {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, EYE_Y, EYE_W, EYE_H, 10, WHITE);
  display.fillRoundRect(RIGHT_X, EYE_Y, EYE_W, EYE_H, 10, WHITE);

  display.fillCircle(LEFT_X + 19, 24, 8, BLACK);
  display.fillCircle(RIGHT_X + 19, 24, 8, BLACK);

  display.display();
  delay(1800);
}

// 10. SAD EYES WITH TEARS
void sadEyes() {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, 15, EYE_W, 35, 9, WHITE);
  display.fillRoundRect(RIGHT_X, 15, EYE_W, 35, 9, WHITE);

  display.fillCircle(LEFT_X + 19, 32, 8, BLACK);
  display.fillCircle(RIGHT_X + 19, 32, 8, BLACK);

  display.fillCircle(35, 49, 4, WHITE);
  display.fillCircle(85, 49, 4, WHITE);

  display.display();

  for (int y = 45; y <= 60; y += 3) {
    display.fillCircle(35, y, 3, WHITE);
    display.fillCircle(85, y, 3, WHITE);
    display.display();
    delay(150);
  }

  delay(1000);
}

// COMMON FUNCTION: DRAW EYES
void drawEyes(int h) {
  display.clearDisplay();

  int y = 32 - h / 2;

  display.fillRoundRect(LEFT_X, y, EYE_W, h, 8, WHITE);
  display.fillRoundRect(RIGHT_X, y, EYE_W, h, 8, WHITE);

  display.display();
}

// COMMON FUNCTION: PUPIL MOVEMENT
void drawPupils(int offsetX, int offsetY) {
  display.clearDisplay();

  display.fillRoundRect(LEFT_X, EYE_Y, EYE_W, EYE_H, 9, WHITE);
  display.fillRoundRect(RIGHT_X, EYE_Y, EYE_W, EYE_H, 9, WHITE);

  display.fillCircle(LEFT_X + 19 + offsetX,
                     32 + offsetY, 9, BLACK);

  display.fillCircle(RIGHT_X + 19 + offsetX,
                     32 + offsetY, 9, BLACK);

  display.display();
}
