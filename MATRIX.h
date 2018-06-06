#pragma once

#include <RGBmatrixPanel.h> // Hardware-specific library
#include "BALL.h"
#include "PUCK.h"

#define ROWS 16
#define COLUMNS 32

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void black() {
  //Clears Display
  for (uint8_t x = 0; x < 32; x++) {
    for (uint8_t y = 0; y < 16; y++) {
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
    }
  }
}

void black(int x, int y) {
  //Clears Pixel
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
}

void drawRow(int row) {
  for (uint8_t x = 0; x < COLUMNS; x++) {
    matrix.drawPixel(x, row, matrix.Color333(3, 3, 3));
  }
}

void drawColumn(int column) {
  for (uint8_t y = 0; y < ROWS; y++) {
    matrix.drawPixel(column, y, matrix.Color333(3, 3, 3));
  }
}

void drawBall(BALL &ball, bool clear) {
  if (clear) {
    matrix.drawPixel(ball.x, ball.y, matrix.Color333(0, 0, 0));
  }
  else {
    matrix.drawPixel(ball.x, ball.y, matrix.Color333(3, 0, 0));
  }
}

void drawPuck(PUCK puck, int r, int g, int b) {
  for (int h = 0; h < puck.height; h++) {
    matrix.drawPixel(puck.x, puck.y + h, matrix.Color333(r, g, b));
  }
}