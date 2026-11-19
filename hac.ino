
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define W 128
#define H 64
#define OLED_ADDR 0x3C
#define TOTAL 15
#define SPEED 35
#define DURATION 4000

Adafruit_SSD1306 display(W, H, &Wire, -1);

int scene = 0;
int frame = 0;
unsigned long previous = 0;
unsigned long sceneTime = 0;

// HEADER ONLY - NO FOOTER
void header(const char *name) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  display.print(name);
  display.drawLine(0, 12, 127, 12, WHITE);
}

void centerText(const char *s, int y, int size) {
  display.setTextSize(size);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(s, 0, y, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, y);
  display.print(s);
}

// 1. DIGITAL SKULL
void skull() {
  header("DIGITAL SKULL");

  int eye = frame % 20 < 10 ? 4 : 2;

  display.drawRoundRect(42, 17, 44, 34, 12, WHITE);
  display.fillCircle(54, 31, eye, WHITE);
  display.fillCircle(74, 31, eye, WHITE);
  display.drawTriangle(64, 36, 59, 43, 69, 43, WHITE);

  for (int i = 0; i < 5; i++) {
    display.drawLine(51 + i * 6, 46, 51 + i * 6, 52, WHITE);
  }
}

// 2. FINGERPRINT
void fingerprint() {
  header("FINGERPRINT");

  int r = 5 + frame % 18;

  display.drawCircle(64, 34, r, WHITE);
  display.drawCircle(64, 34, r + 5, WHITE);
  display.drawCircle(64, 34, r + 10, WHITE);
  display.drawLine(45, 34, 83, 34, WHITE);

  display.setCursor(3, 49);
  display.print(frame % 2 ? "SCANNING..." : "IDENTIFYING");
}

// 3. FACE RECOGNITION
void faceScan() {
  header("FACE RECOGNITION");

  display.drawRoundRect(43, 17, 42, 35, 10, WHITE);
  display.fillCircle(54, 30, 3, WHITE);
  display.fillCircle(74, 30, 3, WHITE);
  display.drawLine(57, 42, 71, 42, WHITE);

  int y = 17 + frame % 35;
  display.drawLine(43, y, 85, y, WHITE);
}

// 4. CIRCUIT BOARD
void circuit() {
  header("CIRCUIT BOARD");

  for (int i = 0; i < 6; i++) {
    int x = 8 + i * 21;
    int y = 20 + ((i * 13 + frame * 2) % 29);

    display.drawLine(x, 17, x, y, WHITE);
    display.drawLine(x, y, x + 10, y, WHITE);
    display.fillCircle(x + 10, y, 2, WHITE);
  }

  display.drawRect(43, 25, 42, 22, WHITE);
  display.setCursor(53, 32);
  display.print("CPU");
}

// 5. ROBOT FACE
void robotFace() {
  header("ROBOT FACE");

  int blink = frame % 30 < 3 ? 1 : 5;

  display.drawRoundRect(30, 18, 68, 34, 8, WHITE);
  display.fillRoundRect(42, 27, 12, blink, 3, WHITE);
  display.fillRoundRect(74, 27, 12, blink, 3, WHITE);
  display.drawLine(51, 43, 77, 43, WHITE);
  display.drawLine(36, 12, 36, 18, WHITE);
  display.drawLine(92, 12, 92, 18, WHITE);
}

// 6. DIGITAL DNA
void dna() {
  header("DNA SEQUENCE");

  for (int y = 15; y < 54; y += 3) {
    float a = y * 0.25 + frame * 0.15;
    int x1 = 64 + sin(a) * 22;
    int x2 = 64 - sin(a) * 22;

    display.drawPixel(x1, y, WHITE);
    display.drawPixel(x2, y, WHITE);

    if (y % 6 == 0) {
      display.drawLine(x1, y, x2, y, WHITE);
    }
  }
}

// 7. GLITCH
void glitch() {
  header("GLITCH MODE");

  for (int i = 0; i < 12; i++) {
    int x = random(0, 120);
    int y = random(15, 53);
    int w = random(3, 24);
    display.drawFastHLine(x, y, w, WHITE);
  }

  if (frame % 3 == 0) {
    display.drawRect(20, 20, 90, 28, WHITE);
    display.setCursor(37, 31);
    display.print("GLITCH");
  }
}

// 8. UFO
void ufo() {
  header("UFO SIGNAL");

  int x = 20 + (frame * 2) % 88;

  display.drawEllipse(x, 31, 18, 7, WHITE);
  display.drawLine(x - 9, 28, x - 5, 20, WHITE);
  display.drawLine(x + 9, 28, x + 5, 20, WHITE);
  display.drawLine(x - 5, 20, x + 5, 20, WHITE);
  display.drawLine(x - 9, 39, x - 14, 48, WHITE);
  display.drawLine(x, 39, x, 49, WHITE);
  display.drawLine(x + 9, 39, x + 14, 48, WHITE);
}

// 9. WORMHOLE
void wormhole() {
  header("SPACE WORMHOLE");

  for (int i = 0; i < 6; i++) {
    int r = 4 + ((i * 6 + frame * 2) % 28);
    display.drawCircle(64, 35, r, WHITE);
  }
}

// 10. ELECTRIC PULSE
void electric() {
  header("ELECTRIC PULSE");

  int x = 3;

  for (int i = 0; i < 15; i++) {
    int y = 30 + random(-12, 13);
    display.drawLine(x, 30, x + 8, y, WHITE);
    x += 8;
  }
}

// 11. HEARTBEAT
void heartbeat() {
  header("HEARTBEAT");

  int points[] = {
    0, 0, 0, -5, 0, 0, 18, -19,
    0, 0, -6, 0, 0, 0, 0, 0
  };

  int shift = frame % 16;

  for (int i = 0; i < 15; i++) {
    int x1 = 4 + i * 8;
    int x2 = x1 + 8;

    int y1 = 34 - points[(i + shift) % 16];
    int y2 = 34 - points[(i + 1 + shift) % 16];

    display.drawLine(x1, y1, x2, y2, WHITE);
  }
}

// 12. CYBER SHIELD
void shield() {
  header("CYBER SHIELD");

  display.drawTriangle(64, 16, 35, 27, 42, 45, WHITE);
  display.drawTriangle(64, 16, 93, 27, 86, 45, WHITE);
  display.drawLine(42, 45, 64, 53, WHITE);
  display.drawLine(86, 45, 64, 53, WHITE);
  display.drawLine(53, 34, 62, 42, WHITE);
  display.drawLine(62, 42, 78, 27, WHITE);
}

// 13. HOLOGRAM
void hologram() {
  header("HOLOGRAM");

  for (int y = 17; y < 52; y += 4) {
    display.drawFastHLine(30, y, 68, WHITE);
  }

  int r = 5 + frame % 16;
  display.drawCircle(64, 34, r, WHITE);
  display.drawCircle(64, 34, r / 2, WHITE);
}

// 14. ROTATING 3D CUBE
void cube() {
  header("3D CUBE");

  float a = frame * 0.08;
  int x[8], y[8];

  for (int i = 0; i < 8; i++) {
    float px = (i & 1) ? 14 : -14;
    float py = (i & 2) ? 14 : -14;
    float pz = (i & 4) ? 14 : -14;

    float rx = px * cos(a) - pz * sin(a);
    float rz = px * sin(a) + pz * cos(a);

    x[i] = 64 + rx;
    y[i] = 34 + py * cos(a * 0.7) - rz * sin(a * 0.7);
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      int k = i ^ (1 << j);

      if (i < k) {
        display.drawLine(x[i], y[i], x[k], y[k], WHITE);
      }
    }
  }
}

// 15. DIGITAL PORTAL
void portal() {
  header("DIGITAL PORTAL");

  float a = frame * 0.12;

  for (int i = 0; i < 4; i++) {
    int r = 7 + i * 7;
    int x = 64 + cos(a + i) * 8;
    int y = 34 + sin(a + i) * 5;

    display.drawCircle(x, y, r, WHITE);
  }
}

void setup() {
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) {}
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  centerText("CYBERPUNK V3", 25, 2);
  display.display();

  delay(1000);
  sceneTime = millis();
}

void loop() {
  if (millis() - previous < SPEED) return;
  previous = millis();

  if (millis() - sceneTime >= DURATION) {
    scene = (scene + 1) % TOTAL;
    sceneTime = millis();
    frame = 0;
  }

  switch (scene) {
    case 0: skull(); break;
    case 1: fingerprint(); break;
    case 2: faceScan(); break;
    case 3: circuit(); break;
    case 4: robotFace(); break;
    case 5: dna(); break;
    case 6: glitch(); break;
    case 7: ufo(); break;
    case 8: wormhole(); break;
    case 9: electric(); break;
    case 10: heartbeat(); break;
    case 11: shield(); break;
    case 12: hologram(); break;
    case 13: cube(); break;
    case 14: portal(); break;
  }

  display.display();
  frame++;
}
