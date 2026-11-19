
/*
 * Project: 30 Robot Eyes Emotions
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf. All rights reserved.
 *
 * Hardware:
 * Arduino UNO
 * SSD1306 OLED 128x64 I2C
 *
 * No buttons, no sensors, no extra hardware.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

#define LX 20
#define RX 70
#define EY 13
#define EW 38
#define EH 38

int emotion = 0;
int frame = 0;

unsigned long lastChange = 0;
unsigned long lastFrame = 0;

const int TOTAL = 30;
const unsigned long EMOTION_TIME = 2500;
const unsigned long FRAME_TIME = 45;

// ---------------- SETUP ----------------

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {}
  }

  display.clearDisplay();
  display.display();
}

// ---------------- MAIN LOOP ----------------

void loop() {

  unsigned long now = millis();

  if (now - lastChange >= EMOTION_TIME) {
    lastChange = now;
    emotion = (emotion + 1) % TOTAL;
    frame = 0;
  }

  if (now - lastFrame >= FRAME_TIME) {
    lastFrame = now;
    frame++;
    drawEmotion(emotion, frame);
  }
}

// ---------------- DRAW EYES ----------------

void drawNormal(int height = EH, int offsetX = 0,
                int offsetY = 0) {

  display.clearDisplay();

  int y = 32 - height / 2 + offsetY;

  display.fillRoundRect(
    LX + offsetX, y, EW, height, 9, WHITE
  );

  display.fillRoundRect(
    RX + offsetX, y, EW, height, 9, WHITE
  );

  display.display();
}

void drawPupils(int px, int py) {

  display.clearDisplay();

  display.fillRoundRect(LX, EY, EW, EH, 9, WHITE);
  display.fillRoundRect(RX, EY, EW, EH, 9, WHITE);

  display.fillCircle(LX + 19 + px, 32 + py, 9, BLACK);
  display.fillCircle(RX + 19 + px, 32 + py, 9, BLACK);

  display.display();
}

void drawRoundEyes(int radius, int pupil) {

  display.clearDisplay();

  display.fillCircle(39, 32, radius, WHITE);
  display.fillCircle(89, 32, radius, WHITE);

  display.fillCircle(39, 32, pupil, BLACK);
  display.fillCircle(89, 32, pupil, BLACK);

  display.display();
}

// ---------------- ANIMATION ENGINE ----------------

void drawEmotion(int id, int f) {

  int blink = abs((f % 30) - 15);

  switch (id) {

    // 1 NORMAL
    case 0:
      drawNormal();
      break;

    // 2 BLINK
    case 1: {
      int h = 4 + abs((f % 24) - 12) * 3;
      if (h > 38) h = 38;
      drawNormal(h);
      break;
    }

    // 3 HAPPY
    case 2:
      display.clearDisplay();
      display.fillRoundRect(20, 20, 38, 25, 12, WHITE);
      display.fillRoundRect(70, 20, 38, 25, 12, WHITE);
      display.fillCircle(39, 12, 17, BLACK);
      display.fillCircle(89, 12, 17, BLACK);
      display.display();
      break;

    // 4 LOOK LEFT
    case 3:
      drawPupils(-9, 0);
      break;

    // 5 LOOK RIGHT
    case 4:
      drawPupils(9, 0);
      break;

    // 6 SLEEPY
    case 5: {
      int h = 10 + abs((f % 40) - 20);
      if (h > 30) h = 30;
      drawNormal(h);
      break;
    }

    // 7 ANGRY
    case 6:
      display.clearDisplay();
      display.fillRoundRect(20, 18, 38, 34, 7, WHITE);
      display.fillRoundRect(70, 18, 38, 34, 7, WHITE);
      display.fillTriangle(20, 8, 58, 23, 58, 8, BLACK);
      display.fillTriangle(70, 23, 108, 8, 108, 8, BLACK);
      display.fillCircle(39, 38, 8, BLACK);
      display.fillCircle(89, 38, 8, BLACK);
      display.display();
      break;

    // 8 SURPRISED
    case 7:
      drawRoundEyes(19, 6);
      break;

    // 9 CURIOUS
    case 8:
      drawPupils(0, -9);
      break;

    // 10 SAD
    case 9:
      drawNormal(32, 0, 3);
      display.fillCircle(35, 49, 3, WHITE);
      display.fillCircle(85, 49, 3, WHITE);
      display.display();
      break;

    // 11 EXCITED
    case 10:
      drawRoundEyes(20, 10);
      break;

    // 12 LOVE
    case 11:
      display.clearDisplay();
      drawHeart(39, 32, 15);
      drawHeart(89, 32, 15);
      display.display();
      break;

    // 13 CONFUSED
    case 12:
      display.clearDisplay();
      display.fillRoundRect(20, 17, 38, 38, 9, WHITE);
      display.fillRoundRect(70, 17, 38, 38, 9, WHITE);
      display.fillCircle(32, 32, 8, BLACK);
      display.fillCircle(94, 28, 8, BLACK);
      display.display();
      break;

    // 14 SHOCKED
    case 13:
      drawRoundEyes(21, 4);
      break;

    // 15 CRYING
    case 14:
      display.clearDisplay();
      display.fillRoundRect(20, 15, 38, 35, 9, WHITE);
      display.fillRoundRect(70, 15, 38, 35, 9, WHITE);
      display.fillCircle(39, 32, 8, BLACK);
      display.fillCircle(89, 32, 8, BLACK);
      display.fillCircle(39, 52 + (f % 8), 4, WHITE);
      display.fillCircle(89, 52 + (f % 8), 4, WHITE);
      display.display();
      break;

    // 16 LAUGHING
    case 15:
      display.clearDisplay();
      display.fillRoundRect(20, 20, 38, 25, 15, WHITE);
      display.fillRoundRect(70, 20, 38, 25, 15, WHITE);
      display.fillCircle(39, 12, 17, BLACK);
      display.fillCircle(89, 12, 17, BLACK);
      display.display();
      break;

    // 17 SUSPICIOUS
    case 16:
      drawPupils((f % 20 < 10) ? -7 : 7, 4);
      break;

    // 18 EXHAUSTED
    case 17:
      drawNormal(12 + (f % 10));
      break;

    // 19 WINK
    case 18:
      display.clearDisplay();
      display.fillRoundRect(20, 20, 38, 10, 6, WHITE);
      display.fillRoundRect(70, 13, 38, 38, 9, WHITE);
      display.fillCircle(89, 32, 8, BLACK);
      display.display();
      break;

    // 20 DIZZY
    case 19:
      display.clearDisplay();
      drawSpiral(39, 32);
      drawSpiral(89, 32);
      display.display();
      break;

    // 21 SHY
    case 20:
      drawPupils(0, 8);
      break;

    // 22 MISCHIEVOUS
    case 21:
      display.clearDisplay();
      display.fillRoundRect(20, 18, 38, 35, 9, WHITE);
      display.fillRoundRect(70, 18, 38, 35, 9, WHITE);
      display.fillCircle(39, 39, 8, BLACK);
      display.fillCircle(89, 39, 8, BLACK);
      display.display();
      break;

    // 23 FOCUSED
    case 22:
      drawPupils(0, 0);
      break;

    // 24 YAWNING
    case 23:
      drawRoundEyes(16 + (f % 8), 5);
      break;

    // 25 FURIOUS
    case 24:
      display.clearDisplay();
      display.fillRoundRect(20, 18, 38, 34, 7, WHITE);
      display.fillRoundRect(70, 18, 38, 34, 7, WHITE);
      display.fillTriangle(20, 5, 58, 28, 58, 5, BLACK);
      display.fillTriangle(70, 28, 108, 5, 108, 5, BLACK);
      display.fillCircle(39, 38, 10, BLACK);
      display.fillCircle(89, 38, 10, BLACK);
      display.display();
      break;

    // 26 WORRIED
    case 25:
      display.clearDisplay();
      display.fillRoundRect(20, 19, 38, 35, 9, WHITE);
      display.fillRoundRect(70, 19, 38, 35, 9, WHITE);
      display.fillCircle(39, 38, 8, BLACK);
      display.fillCircle(89, 38, 8, BLACK);
      display.display();
      break;

    // 27 COOL
    case 26:
      display.clearDisplay();
      display.fillRoundRect(18, 23, 42, 22, 5, WHITE);
      display.fillRoundRect(68, 23, 42, 22, 5, WHITE);
      display.fillRect(60, 29, 8, 4, WHITE);
      display.display();
      break;

    // 28 THINKING
    case 27:
      drawPupils(5, -9);
      break;

    // 29 RELAXED
    case 28:
      drawNormal(20);
      break;

    // 30 PLAYFUL
    case 29:
      if (f % 20 < 10) {
        drawPupils(-7, -4);
      } else {
        drawPupils(7, 4);
      }
      break;
  }
}

// ---------------- HEART DRAWING ----------------

void drawHeart(int x, int y, int size) {

  display.fillCircle(x - size / 3, y - size / 4,
                     size / 3, WHITE);

  display.fillCircle(x + size / 3, y - size / 4,
                     size / 3, WHITE);

  display.fillTriangle(
    x - size, y - size / 5,
    x + size, y - size / 5,
    x, y + size, WHITE
  );
}

// ---------------- SPIRAL EYES ----------------

void drawSpiral(int x, int y) {

  display.drawCircle(x, y, 12, WHITE);
  display.drawCircle(x, y, 7, WHITE);
  display.drawPixel(x + 2, y - 2, WHITE);
}
