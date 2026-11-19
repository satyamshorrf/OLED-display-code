
/*
 * Project: 0.96" OLED Spotify-Style Lyrics Player
 * Author: Satyam Shorrf
 * GitHub: @satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf.
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

int animationMode = 0;
int currentLine = 0;
int frameNo = 0;

unsigned long lastFrame = 0;
const int frameDelay = 100;

// ---------------- HEADER ----------------

void drawHeader() {
  display.fillRoundRect(0, 0, 128, 13, 3, WHITE);

  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(3, 3);
  display.print(songTitle);

  display.setTextColor(WHITE);
}

// ---------------- PROGRESS ----------------

void drawProgress() {
  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);

  int w = map(currentLine + 1, 0, totalLines, 0, 120);

  display.fillRoundRect(4, 59, w, 2, 1, WHITE);
}

// ---------------- LYRICS ----------------

void drawLyrics() {
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(3, 23);
  display.println(lyrics[currentLine]);
}

// 01 SPOTIFY EQUALIZER

void animation1() {
  drawLyrics();

  for (int i = 0; i < 8; i++) {
    int h = random(3, 17);

    display.fillRect(
      9 + i * 15,
      48 - h,
      5, h,
      WHITE
    );
  }
}

// 02 TYPEWRITER

void animation2() {
  const char* txt = lyrics[currentLine];

  int len = strlen(txt);
  int chars = frameNo % (len + 1);

  display.setTextSize(1);
  display.setCursor(3, 29);
  display.setTextColor(WHITE);

  for (int i = 0; i < chars; i++) {
    display.write(txt[i]);
  }

  display.drawLine(
    3 + chars * 6, 28,
    3 + chars * 6, 38,
    WHITE
  );
}

// 03 SCROLLING TEXT

void animation3() {
  const char* txt = lyrics[currentLine];

  int len = strlen(txt);
  int offset = frameNo % (len * 6 + 128);

  display.setTextSize(1);
  display.setCursor(128 - offset, 32);
  display.print(txt);
}

// 04 BOUNCING BALL

void animation4() {
  drawLyrics();

  int x = (frameNo * 4) % 120;
  int y = 43 + abs((frameNo % 16) - 8);

  display.fillCircle(x + 4, y, 3, WHITE);
}

// 05 WAVEFORM

void animation5() {
  drawLyrics();

  for (int x = 0; x < 128; x += 4) {
    int h = random(2, 13);

    display.drawLine(
      x, 48 - h,
      x, 48 + h,
      WHITE
    );
  }
}

// 06 HEARTBEAT

void animation6() {
  drawLyrics();

  int size = (frameNo % 8 < 4) ? 2 : 1;

  int cx = 64;
  int cy = 45;

  display.fillCircle(cx - 4 * size, cy, 4 * size, WHITE);
  display.fillCircle(cx + 4 * size, cy, 4 * size, WHITE);

  display.fillTriangle(
    cx - 8 * size, cy,
    cx + 8 * size, cy,
    cx, cy + 12 * size,
    WHITE
  );
}

// 07 PARTICLES

void animation7() {
  drawLyrics();

  for (int i = 0; i < 18; i++) {
    int x = random(0, 128);
    int y = random(16, 55);

    display.drawPixel(x, y, WHITE);
  }
}

// 08 CIRCULAR LOADER

void animation8() {
  drawLyrics();

  int angle = frameNo * 20;

  int x = 64 + cos(radians(angle)) * 12;
  int y = 45 + sin(radians(angle)) * 9;

  display.drawCircle(64, 45, 13, WHITE);
  display.fillCircle(x, y, 3, WHITE);
}

// 09 PIXEL REVEAL

void animation9() {
  const char* txt = lyrics[currentLine];

  display.setTextSize(1);
  display.setCursor(3, 30);
  display.setTextColor(WHITE);
  display.print(txt);

  int count = frameNo % 25;

  for (int i = 0; i < count; i++) {
    int x = random(0, 128);
    int y = random(17, 54);

    display.drawPixel(x, y, BLACK);
  }
}

// 10 GLITCH

void animation10() {
  drawLyrics();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  int shift = random(-3, 4);

  display.setCursor(3 + shift, 30);
  display.print(lyrics[currentLine]);

  for (int i = 0; i < 5; i++) {
    int y = random(17, 55);
    int x = random(0, 110);

    display.drawFastHLine(
      x, y, random(3, 18), WHITE
    );
  }
}

// ---------------- SETUP ----------------

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  if (!display.begin(
    SSD1306_SWITCHCAPVCC, 0x3C
  )) {
    Serial.println("OLED not found!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(20, 18);
  display.println("SATYAM SHORRF");

  display.setCursor(25, 35);
  display.println("@satyamshorrf");

  display.display();
  delay(2000);
}

// ---------------- MAIN LOOP ----------------

void loop() {
  unsigned long now = millis();

  if (now - lastFrame < frameDelay) return;
  lastFrame = now;

  display.clearDisplay();

  drawHeader();

  switch (animationMode) {
    case 0: animation1(); break;
    case 1: animation2(); break;
    case 2: animation3(); break;
    case 3: animation4(); break;
    case 4: animation5(); break;
    case 5: animation6(); break;
    case 6: animation7(); break;
    case 7: animation8(); break;
    case 8: animation9(); break;
    case 9: animation10(); break;
  }

  drawProgress();

  display.display();

  frameNo++;

  // Change animation after 50 frames
  if (frameNo >= 50) {
    frameNo = 0;

    animationMode++;

    if (animationMode >= 10) {
      animationMode = 0;

      currentLine++;

      if (currentLine >= totalLines) {
        currentLine = 0;
      }
    }
  }
}
