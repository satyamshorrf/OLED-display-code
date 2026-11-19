
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(W, H, &Wire, -1);

int scene = 0;
int frame = 0;
unsigned long lastFrame = 0;
unsigned long sceneTime = 0;

int drops[16];
int speeds[16];
int radar = 0;

void setup() {
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20, 25);
  display.print("HACKER CONSOLE");
  display.setCursor(30, 40);
  display.print("BOOTING...");
  display.display();

  for (int i = 0; i < 16; i++) {
    drops[i] = random(-64, 0);
    speeds[i] = random(1, 4);
  }

  delay(1000);
  sceneTime = millis();
}

void header(const char *name) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(">> ");
  display.print(name);
  display.drawLine(0, 10, 127, 10, WHITE);
}

void footer() {
  display.drawLine(0, 55, 127, 55, WHITE);
  display.setCursor(2, 57);
  display.print("CYBER CONSOLE V2");
}

void matrix() {
  header("MATRIX RAIN");

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 5; j++) {
      int y = drops[i] - j * 8;
      if (y > 10 && y < 55) {
        display.setCursor(i * 8, y);
        display.print(random(0, 2));
      }
    }

    drops[i] += speeds[i];

    if (drops[i] > 64) {
      drops[i] = random(-30, 0);
    }
  }

  footer();
}

void skull() {
  header("DIGITAL SKULL");

  display.drawRoundRect(43, 14, 42, 35, 12, WHITE);
  display.fillCircle(54, 29, 5, WHITE);
  display.fillCircle(74, 29, 5, WHITE);

  display.drawTriangle(64, 34, 59, 41, 69, 41, WHITE);

  display.drawLine(51, 45, 51, 51, WHITE);
  display.drawLine(58, 45, 58, 51, WHITE);
  display.drawLine(65, 45, 65, 51, WHITE);
  display.drawLine(72, 45, 72, 51, WHITE);
  display.drawLine(79, 45, 79, 51, WHITE);

  footer();
}

void password() {
  header("PASSWORD TEST");

  display.setCursor(5, 17);
  display.print("TARGET: LOCAL DEMO");

  display.setCursor(5, 29);
  display.print("KEY: ");

  for (int i = 0; i < 8; i++) {
    display.print(random(0, 10));
  }

  int p = (frame * 3) % 101;

  display.drawRect(5, 43, 118, 9, WHITE);
  display.fillRect(6, 44, p * 116 / 100, 7, WHITE);

  display.setCursor(5, 34);
  display.print("TESTING...");

  footer();
}

void terminal() {
  header("ROOT TERMINAL");

  display.setCursor(3, 15);
  display.print("> root@cyber");

  display.setCursor(3, 24);
  display.print("> initializing");

  display.setCursor(3, 33);
  display.print("> loading modules");

  display.setCursor(3, 42);
  display.print("> access simulation");

  display.setCursor(3, 49);
  display.print("> ");
  display.print(frame % 2 ? "_" : "READY");

  footer();
}

void radarScreen() {
  header("CYBER RADAR");

  int cx = 64;
  int cy = 33;

  display.drawCircle(cx, cy, 22, WHITE);
  display.drawCircle(cx, cy, 12, WHITE);
  display.drawLine(cx - 22, cy, cx + 22, cy, WHITE);
  display.drawLine(cx, cy - 22, cx, cy + 22, WHITE);

  float a = radar * 0.0174533;
  int x = cx + cos(a) * 22;
  int y = cy + sin(a) * 22;

  display.drawLine(cx, cy, x, y, WHITE);

  radar = (radar + 15) % 360;

  footer();
}

void decrypt() {
  header("DATA DECRYPT");

  display.setCursor(5, 15);
  display.print("DECODING...");

  for (int i = 0; i < 4; i++) {
    display.setCursor(5, 25 + i * 7);

    for (int j = 0; j < 14; j++) {
      display.print(char(random(65, 91)));
    }
  }

  footer();
}

void firewall() {
  header("FIREWALL TEST");

  display.drawRect(5, 15, 118, 34, WHITE);

  for (int i = 0; i < 7; i++) {
    int x = 10 + i * 16;
    display.drawRect(x, 20, 10, 24, WHITE);
  }

  display.setCursor(12, 50);
  display.print("SIMULATION ONLY");

  footer();
}

void network() {
  header("NETWORK MAP");

  display.drawCircle(64, 31, 7, WHITE);
  display.drawCircle(15, 19, 5, WHITE);
  display.drawCircle(112, 19, 5, WHITE);
  display.drawCircle(15, 47, 5, WHITE);
  display.drawCircle(112, 47, 5, WHITE);

  display.drawLine(64, 31, 15, 19, WHITE);
  display.drawLine(64, 31, 112, 19, WHITE);
  display.drawLine(64, 31, 15, 47, WHITE);
  display.drawLine(64, 31, 112, 47, WHITE);

  footer();
}

void systemBreach() {
  header("SECURITY ALERT");

  display.drawRect(3, 13, 122, 40, WHITE);

  if (frame % 2 == 0) {
    display.setTextSize(2);
    display.setCursor(17, 20);
    display.print("WARNING!");
  } else {
    display.setTextSize(1);
    display.setCursor(20, 26);
    display.print("SYSTEM BREACH");
  }

  display.setTextSize(1);
  display.setCursor(23, 43);
  display.print("DEMO ALERT");

  footer();
}

void binary() {
  header("BINARY STREAM");

  for (int i = 0; i < 6; i++) {
    display.setCursor(4, 14 + i * 7);

    for (int j = 0; j < 19; j++) {
      display.print(random(0, 2));
    }
  }

  footer();
}

void lockScreen() {
  header("DIGITAL LOCK");

  display.drawRoundRect(27, 17, 74, 32, 5, WHITE);
  display.drawCircle(64, 28, 7, WHITE);
  display.drawLine(64, 35, 64, 42, WHITE);

  display.setCursor(35, 51);
  display.print("LOCKED");

  footer();
}

void server() {
  header("SERVER STATUS");

  for (int i = 0; i < 4; i++) {
    display.setCursor(5, 15 + i * 9);
    display.print("SERVER 0");
    display.print(i + 1);
    display.print(" : ");
    display.print(random(0, 10) > 1 ? "ONLINE" : "OFFLINE");
  }

  footer();
}

void satellite() {
  header("SATELLITE LINK");

  display.drawCircle(64, 31, 7, WHITE);
  display.drawRect(39, 12, 10, 8, WHITE);
  display.drawRect(79, 12, 10, 8, WHITE);
  display.drawLine(57, 24, 48, 20, WHITE);
  display.drawLine(71, 24, 80, 20, WHITE);
  display.drawCircle(64, 31, 19, WHITE);

  display.setCursor(5, 47);
  display.print("SIGNAL: ");
  display.print(random(60, 100));
  display.print("%");

  footer();
}

void loop() {
  if (millis() - lastFrame < 45) return;
  lastFrame = millis();

  if (millis() - sceneTime > 4000) {
    scene = (scene + 1) % 12;
    sceneTime = millis();
    frame = 0;
  }

  switch (scene) {
    case 0: matrix(); break;
    case 1: skull(); break;
    case 2: password(); break;
    case 3: terminal(); break;
    case 4: radarScreen(); break;
    case 5: decrypt(); break;
    case 6: firewall(); break;
    case 7: network(); break;
    case 8: systemBreach(); break;
    case 9: binary(); break;
    case 10: lockScreen(); break;
    case 11: server(); break;
  }

  display.display();
  frame++;
}
