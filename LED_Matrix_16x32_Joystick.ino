// testcolors demo for Adafruit RGBmatrixPanel library.
// Renders 512 colors on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// Library supports 4096 colors, but there aren't that many pixels!  :)

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library

#include "BALL.h"
#include "JOYSTICK.h"
#include "MATRIX.h"
#include "PUCK.h"
#include "SCORE.h"
#include "VELOCITY.h"

#define DEMO 0
#define ONE_PLAYER 1
#define TWO_PLAYER 2

#define DIFFICULTY_LEVEL 7
#define ROWS 16
#define COLUMNS 32

int reset = 0;
int JSX1 = 0, JSY1 = 0;
int state = 0;

int mode = DEMO;

PUCK puckLeft;
PUCK puckRight;
BALL ball;
SCORES score;

void resetState(bool gameOver) {
  black();
  setUpScreen();
  initializePucks(puckLeft, puckRight);
  initializeBall(ball, ROWS, COLUMNS);
  if (gameOver) {
    initializeScore(score);
  }
  delay(50);
}

void scrollText(char* text) {
  matrix.setTextWrap(false);
  black();
  int cursorX = matrix.width();

  while (cursorX > -COLUMNS * 3) {
    matrix.setTextColor(matrix.Color333(0, 0, 0));
    matrix.setCursor(cursorX, 1);
    matrix.print(text);
    cursorX--;
    matrix.setTextColor(matrix.Color333(3, 3, 3));
    matrix.setCursor(cursorX, 1);
    matrix.print(text);
    delay(25);
  }
}

void printScores() {
  char scoreString[6];
  scoreString[0] = score.player0 + '0';
  scoreString[1] = ' ';
  scoreString[2] = '-';
  scoreString[3] = ' ';
  scoreString[4] = score.player1 + '0';
  scoreString[5] = NULL;
  scrollText(scoreString);
  if (!checkScores()) {
    resetState(false);
  }

}

void setUpScreen() {
  drawRow(0);
  drawRow(ROWS - 1);
  drawColumn(0);
  drawColumn(COLUMNS - 1);
}

void eraseOldPucks() {
  drawPuck(puckLeft, 0, 0, 0);
  drawPuck(puckRight, 0, 0, 0);
}

void drawNewPucks(PUCK &puckLeft, PUCK &puckRight) {
  drawPuck(puckLeft, puckLeft.r, puckLeft.g, puckLeft.b);
  drawPuck(puckRight, puckRight.r, puckRight.g, puckRight.b);
}

void readInputs() {
  puckLeft.dir = outputDirection(analogRead(12), analogRead(13));
  reset = digitalRead(13);
}

bool checkScores() {
  if (score.player0 >= scoreToWin) {
    scrollText("Player 0 Wins!");
    resetState(true);
    return true;
  }
  if (score.player1 >= scoreToWin) {
    scrollText("Player 1 Wins!");
    resetState(true);
    return true;
  }  return false;
}

void checkIfScored() {
  int wallIntersection = checkWallIntersection(ball, ROWS, COLUMNS);
  if (wallIntersection != 0) {
    if (wallIntersection == 1) {
      score.player1 += 1;
      printScores();
    }
    if (wallIntersection == 2) {
      score.player0 += 1;
      printScores();
    }
    if (wallIntersection == 3 || wallIntersection == 4) {
      ball.velocity.y *= -1;
    }
  }
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  setUpScreen();
  resetState(true);
}

void loop() {
  
  while (true) {

    if (Serial.available() > 0) { // Checks whether data is comming from the serial port
      state = Serial.read(); // Reads the data from the serial port
      Serial.println(state);
    }

    readInputs();
    if (checkScores()) {
      continue;
    }

    if (!reset) {
      resetState(true);
      delay(100);
    }

    drawBall(ball, true);
    updateBall(puckLeft, puckRight,ball);
    checkIfScored();
    drawBall(ball, false);
    eraseOldPucks();
    

    switch(mode){
      case DEMO:
        //DEMO MODE
        updateJSDirectionAI(puckLeft, ball, DIFFICULTY_LEVEL);
        updateJSDirectionAI(puckRight, ball, DIFFICULTY_LEVEL);
        break;
      case ONE_PLAYER:
        //ONE PLAYER
        updateJSDirection(puckLeft);
        updateJSDirectionAI(puckRight, ball, DIFFICULTY_LEVEL);
        break;
      case TWO_PLAYER:
        //TWO PLAYERS
        updateJSDirection(puckLeft);
        updateJSDirection(puckRight);
        break;       
    }
    
    drawNewPucks(puckLeft, puckRight);
    delay(50);
  }
}
