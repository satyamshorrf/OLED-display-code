
/*
 * Project: OLED Mini Games Collection
 * Author: Satyam Shorrf
 * GitHub: https://github.com/satyamshorrf
 * Copyright (c) 2026 Satyam Shorrf.
 *
 * Hardware: Arduino UNO + SSD1306 128x64
 * Mode: Automatic demo gameplay
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long lastFrame = 0;
unsigned long sceneStart = 0;

int game = 0;
int frame = 0;

// Snake
int snakeX[40], snakeY[40];
int snakeLength = 5;
int snakeDir = 1;
int foodX = 80, foodY = 32;

// Pong
int ballX = 64, ballY = 32;
int ballVX = 2, ballVY = 1;
int paddleY = 25;

// Shooter
int playerX = 64;
int bulletX = -1, bulletY = -1;
int enemyX = 64, enemyY = 20;
int enemyDX = 2;

// Flappy
int birdY = 32;
int birdVelocity = 0;
int pipeX = 128;
int gapY = 32;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {}
  }

  randomSeed(analogRead(A0));
  resetSnake();
  sceneStart = millis();
}

void loop() {
  unsigned long now = millis();

  if (now - lastFrame < 65) return;
  lastFrame = now;

  if (now - sceneStart >= 10000) {
    game = (game + 1) % 4;
    sceneStart = now;
    frame = 0;

    if (game == 0) resetSnake();
    if (game == 1) resetPong();
    if (game == 2) resetShooter();
    if (game == 3) resetFlappy();
  }

  frame++;

  switch (game) {
    case 0: snakeGame(); break;
    case 1: pongGame(); break;
    case 2: spaceShooter(); break;
    case 3: flappyBird(); break;
  }
}

void gameTitle(const char *name) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  display.print(name);
  display.drawLine(0, 12, 127, 12, WHITE);
}

// ---------------- SNAKE GAME ----------------

void resetSnake() {
  snakeLength = 5;
  snakeDir = 1;

  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 40 - i * 4;
    snakeY[i] = 32;
  }

  newFood();
}

void newFood() {
  foodX = random(4, 30) * 4;
  foodY = random(4, 14) * 4;
}

void snakeGame() {
  display.clearDisplay();
  gameTitle("SNAKE GAME - DEMO");

  // Automatic direction changes
  if (frame % 16 == 0) {
    int d = random(4);

    // 0 right, 1 down, 2 left, 3 up
    if ((d + 2) % 4 != snakeDir) snakeDir = d;
  }

  int nx = snakeX[0];
  int ny = snakeY[0];

  if (snakeDir == 0) nx += 4;
  if (snakeDir == 1) ny += 4;
  if (snakeDir == 2) nx -= 4;
  if (snakeDir == 3) ny -= 4;

  if (nx < 0 || nx > 124 || ny < 14 || ny > 60) {
    resetSnake();
    return;
  }

  for (int i = 0; i < snakeLength; i++) {
    if (nx == snakeX[i] && ny == snakeY[i]) {
      resetSnake();
      return;
    }
  }

  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] = nx;
  snakeY[0] = ny;

  if (nx == foodX && ny == foodY) {
    if (snakeLength < 39) snakeLength++;
    newFood();
  }

  display.fillCircle(foodX + 2, foodY + 2, 2, WHITE);

  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], 4, 4, WHITE);
  }

  display.display();
}

// ---------------- PONG GAME ----------------

void resetPong() {
  ballX = 64;
  ballY = 32;
  ballVX = 2;
  ballVY = 1;
  paddleY = 25;
}

void pongGame() {
  display.clearDisplay();
  gameTitle("PONG - DEMO");

  ballX += ballVX;
  ballY += ballVY;

  if (ballY <= 15 || ballY >= 62) ballVY = -ballVY;

  if (ballX >= 119 || ballX <= 7) ballVX = -ballVX;

  // Automatic paddle tracking
  paddleY = ballY - 10;

  if (paddleY < 14) paddleY = 14;
  if (paddleY > 45) paddleY = 45;

  display.fillRect(3, paddleY, 3, 19, WHITE);
  display.fillRect(122, 23, 3, 19, WHITE);

  display.fillCircle(ballX, ballY, 3, WHITE);

  for (int y = 15; y < 64; y += 8) {
    display.drawPixel(64, y, WHITE);
  }

  display.display();
}

// ---------------- SPACE SHOOTER ----------------

void resetShooter() {
  playerX = 64;
  bulletX = -1;
  bulletY = -1;
  enemyX = 64;
  enemyY = 20;
  enemyDX = 2;
}

void spaceShooter() {
  display.clearDisplay();
  gameTitle("SPACE SHOOTER");

  // Automatic player movement
  playerX = 64 + sin(frame * 0.08) * 35;

  // Player spaceship
  display.drawTriangle(
    playerX, 45,
    playerX - 8, 59,
    playerX + 8, 59,
    WHITE
  );

  // Enemy movement
  enemyX += enemyDX;

  if (enemyX < 8 || enemyX > 120) enemyDX = -enemyDX;

  display.drawCircle(enemyX, enemyY, 6, WHITE);
  display.drawLine(enemyX - 4, 20, enemyX + 4, 20, WHITE);

  // Automatic shooting
  if (bulletY < 0) {
    bulletX = playerX;
    bulletY = 43;
  }

  display.drawLine(bulletX, bulletY, bulletX, bulletY - 5, WHITE);
  bulletY -= 4;

  if (bulletY < 14) bulletY = -1;

  if (abs(bulletX - enemyX) < 8 && abs(bulletY - enemyY) < 10) {
    enemyX = random(12, 116);
    bulletY = -1;
  }

  display.display();
}

// ---------------- FLAPPY BIRD ----------------

void resetFlappy() {
  birdY = 32;
  birdVelocity = 0;
  pipeX = 128;
  gapY = 32;
}

void flappyBird() {
  display.clearDisplay();
  gameTitle("FLAPPY BIRD - DEMO");

  // Automatic bird flapping
  if (frame % 12 == 0) {
    birdVelocity = -4;
  }

  birdVelocity++;
  if (birdVelocity > 3) birdVelocity = 3;

  birdY += birdVelocity;

  if (birdY < 15) {
    birdY = 15;
    birdVelocity = 1;
  }

  if (birdY > 59) {
    birdY = 32;
    birdVelocity = -3;
  }

  // Pipes
  pipeX -= 2;

  if (pipeX < -12) {
    pipeX = 128;
    gapY = random(25, 48);
  }

  int topHeight = gapY - 12;
  int bottomY = gapY + 12;

  display.fillRect(pipeX, 13, 12, topHeight - 13, WHITE);
  display.fillRect(pipeX, bottomY, 12, 64 - bottomY, WHITE);

  // Bird
  display.fillCircle(32, birdY, 4, WHITE);
  display.drawPixel(34, birdY - 1, BLACK);

  display.display();
}
