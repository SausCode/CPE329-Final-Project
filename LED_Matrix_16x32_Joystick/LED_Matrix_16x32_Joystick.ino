// testcolors demo for Adafruit RGBmatrixPanel library.
// Renders 512 colors on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// Library supports 4096 colors, but there aren't that many pixels!  :)

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library

#include "BALL.h"
#include "BLUETOOTH.h"
#include "JOYSTICK.h"
#include "MATRIX.h"
#include "PONG.h"
#include "PUCK.h"
#include "SCORE.h"
#include "VELOCITY.h"

#define PONG 0

int gameMode = PONG;

BALL ball;
BLUETOOTH bt;
PUCK puckLeft;
PUCK puckRight;
SCORE score;

void setupSerial() {
  //USB CONNECTION
  Serial.begin(9600);
  //BLUETOOTH CONNECTION
  Serial1.begin(9600);
}

void setupPong() {
  setStartupPuckColors(puckLeft, puckRight);
  setUpScreen();
  resetState(RESET, puckLeft, puckRight, ball, score);
  setDifficultyLevel(7);
  setGameMode(DEMO);
}

void setup() {
  matrix.begin();
  setupPong();
}

void loop() {
  while (true) {
    if (gameMode == PONG) {
      //Checks inputs, reads bluetooth, updates game state
      runPongGame(bt, puckLeft, puckRight, ball, score);
    }
  }
}