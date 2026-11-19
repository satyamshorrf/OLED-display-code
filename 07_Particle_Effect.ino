
/*
 * Project: 0.96" OLED Song Lyrics Display
 * Animation: Floating Particles
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

#define PARTICLE_COUNT 22

int px[PARTICLE_COUNT];
int py[PARTICLE_COUNT];
int speed[PARTICLE_COUNT];

void resetParticle(int i) {
  px[i] = random(0, 128);
  py[i] = random(17, 57);
  speed[i] = random(1, 4);
}

void setup() {
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    while (1);

  for (int i = 0; i < PARTICLE_COUNT; i++)
    resetParticle(i);
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

  for (int i = 0; i < PARTICLE_COUNT; i++) {
    display.drawPixel(px[i], py[i], WHITE);

    if (i % 3 == 0)
      display.drawPixel(px[i] + 1, py[i], WHITE);

    py[i] -= speed[i];

    if (py[i] < 15)
      resetParticle(i);
  }

  display.drawRoundRect(2, 57, 124, 6, 2, WHITE);
  display.fillRect(4, 59,
    map(line + 1, 0, totalLines, 0, 120), 2, WHITE);

  display.display();
  delay(70);

  if (++frame >= 50) {
    frame = 0;
    line = (line + 1) % totalLines;
  }
}
