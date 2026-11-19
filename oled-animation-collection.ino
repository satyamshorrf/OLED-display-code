
/*
 * Project: OLED Animation Collection
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf.
 *
 * Hardware: Arduino UNO + SSD1306 128x64
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long lastFrame = 0;
unsigned long sceneStart = 0;
int scene = 0;
int frame = 0;

int matrixY[16];
int rainX[18], rainY[18];
int starX[12], starY[12];
int snowX[12], snowY[12];

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {}
  }

  randomSeed(analogRead(A0));

  for (int i = 0; i < 16; i++) matrixY[i] = random(64);
  for (int i = 0; i < 18; i++) {
    rainX[i] = random(128);
    rainY[i] = random(64);
  }
  for (int i = 0; i < 12; i++) {
    starX[i] = random(128);
    starY[i] = random(64);
    snowX[i] = random(128);
    snowY[i] = random(64);
  }

  sceneStart = millis();
}

void loop() {
  unsigned long now = millis();

  if (now - lastFrame < 45) return;
  lastFrame = now;

  if (now - sceneStart >= 5000) {
    scene = (scene + 1) % 12;
    sceneStart = now;
    frame = 0;
  }

  frame++;

  switch (scene) {
    case 0: matrixRain(); break;
    case 1: starfield(); break;
    case 2: bouncingBall(); break;
    case 3: radar(); break;
    case 4: rainEffect(); break;
    case 5: rocket(); break;
    case 6: heartbeat(); break;
    case 7: equalizer(); break;
    case 8: loading(); break;
    case 9: snowfall(); break;
    case 10: fireworks(); break;
    case 11: digitalClock(); break;
  }
}

void title(const char *name) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  display.print(name);
  display.drawLine(0, 12, 127, 12, WHITE);
}

// 1. MATRIX RAIN
void matrixRain() {
  display.clearDisplay();
  title("MATRIX RAIN");

  for (int i = 0; i < 16; i++) {
    display.setCursor(i * 8, matrixY[i]);
    display.print(random(0, 2));
    matrixY[i] += random(1, 4);
    if (matrixY[i] > 64) matrixY[i] = 13;
  }

  display.display();
}

// 2. STARFIELD
void starfield() {
  display.clearDisplay();
  title("SPACE TRAVEL");

  for (int i = 0; i < 12; i++) {
    display.drawPixel(starX[i], starY[i], WHITE);
    display.drawPixel(starX[i] + 1, starY[i], WHITE);

    starX[i] -= 1 + (i % 3);

    if (starX[i] < 0) {
      starX[i] = 127;
      starY[i] = random(14, 64);
    }
  }

  display.drawCircle(105, 39, 10, WHITE);
  display.drawCircle(105, 39, 8, WHITE);
  display.display();
}

// 3. BOUNCING BALL
void bouncingBall() {
  static int x = 20, y = 30, vx = 3, vy = 2;

  display.clearDisplay();
  title("BOUNCING BALL");

  x += vx;
  y += vy;

  if (x < 5 || x > 123) vx = -vx;
  if (y < 18 || y > 59) vy = -vy;

  display.drawLine(0, 60, 127, 60, WHITE);
  display.fillCircle(x, y, 4, WHITE);
  display.display();
}

// 4. RADAR
void radar() {
  display.clearDisplay();
  title("RADAR SCAN");

  display.drawCircle(64, 40, 23, WHITE);
  display.drawCircle(64, 40, 15, WHITE);
  display.drawCircle(64, 40, 7, WHITE);
  display.drawLine(64, 16, 64, 63, WHITE);
  display.drawLine(40, 40, 88, 40, WHITE);

  float angle = (frame % 80) * 0.0785;
  int x = 64 + cos(angle) * 23;
  int y = 40 + sin(angle) * 23;

  display.drawLine(64, 40, x, y, WHITE);
  display.fillCircle(75, 29, 2, WHITE);
  display.display();
}

// 5. RAIN
void rainEffect() {
  display.clearDisplay();
  title("RAIN EFFECT");

  for (int i = 0; i < 18; i++) {
    display.drawLine(rainX[i], rainY[i],
                     rainX[i] - 1, rainY[i] + 4, WHITE);

    rainY[i] += 3 + (i % 3);

    if (rainY[i] > 64) {
      rainY[i] = 13;
      rainX[i] = random(128);
    }
  }

  display.display();
}

// 6. ROCKET
void rocket() {
  display.clearDisplay();
  title("ROCKET LAUNCH");

  int y = 55 - (frame % 45);

  display.drawLine(64, y - 12, 64, y + 9, WHITE);
  display.drawTriangle(64, y - 19, 57, y - 9, 71, y - 9, WHITE);
  display.drawLine(57, y + 5, 51, y + 12, WHITE);
  display.drawLine(71, y + 5, 77, y + 12, WHITE);

  display.drawLine(62, y + 10, 60, y + 17, WHITE);
  display.drawLine(66, y + 10, 68, y + 17, WHITE);

  display.display();
}

// 7. HEARTBEAT
void heartbeat() {
  display.clearDisplay();
  title("HEARTBEAT");

  int pulse = (frame % 20 < 10) ? 2 : 0;

  display.drawLine(0, 43, 30, 43, WHITE);
  display.drawLine(30, 43, 38, 43 - pulse, WHITE);
  display.drawLine(38, 43 - pulse, 45, 55, WHITE);
  display.drawLine(45, 55, 54, 20, WHITE);
  display.drawLine(54, 20, 63, 43, WHITE);
  display.drawLine(63, 43, 72, 43, WHITE);
  display.drawLine(72, 43, 80, 34, WHITE);
  display.drawLine(80, 34, 88, 43, WHITE);
  display.drawLine(88, 43, 127, 43, WHITE);

  display.display();
}

// 8. EQUALIZER
void equalizer() {
  display.clearDisplay();
  title("EQUALIZER");

  for (int i = 0; i < 10; i++) {
    int h = random(5, 45);
    int x = 5 + i * 12;
    display.fillRect(x, 60 - h, 7, h, WHITE);
  }

  display.display();
}

// 9. LOADING
void loading() {
  display.clearDisplay();
  title("LOADING");

  display.drawRoundRect(12, 28, 104, 13, 4, WHITE);

  int progress = frame % 100;
  display.fillRect(15, 31, progress, 7, WHITE);

  display.setCursor(53, 49);
  display.print(progress);
  display.print("%");

  display.display();
}

// 10. SNOWFALL
void snowfall() {
  display.clearDisplay();
  title("SNOWFALL");

  for (int i = 0; i < 12; i++) {
    display.drawPixel(snowX[i], snowY[i], WHITE);

    snowY[i] += 1 + (i % 2);
    snowX[i] += (i % 3 == 0) ? 1 : 0;

    if (snowY[i] > 63) {
      snowY[i] = 13;
      snowX[i] = random(128);
    }

    if (snowX[i] > 127) snowX[i] = 0;
  }

  display.display();
}

// 11. FIREWORKS
void fireworks() {
  display.clearDisplay();
  title("FIREWORKS");

  int radius = (frame % 30) / 2;
  int cx = 64, cy = 39;

  for (int i = 0; i < 8; i++) {
    float a = i * 0.785;
    int x = cx + cos(a) * radius;
    int y = cy + sin(a) * radius;
    display.drawLine(cx, cy, x, y, WHITE);
  }

  display.display();
}

// 12. DIGITAL CLOCK / UPTIME
void digitalClock() {
  display.clearDisplay();
  title("ROBOT UPTIME");

  unsigned long seconds = millis() / 1000;
  unsigned int minutes = seconds / 60;
  unsigned int hours = minutes / 60;

  display.setTextSize(2);
  display.setCursor(14, 27);

  if (hours < 10) display.print("0");
  display.print(hours);
  display.print(":");

  if (minutes % 60 < 10) display.print("0");
  display.print(minutes % 60);
  display.print(":");

  if (seconds % 60 < 10) display.print("0");
  display.print(seconds % 60);

  display.setTextSize(1);
  display.setCursor(35, 52);
  display.print("SYSTEM RUNNING");

  display.display();
}
