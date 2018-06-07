#pragma once

#define DEMO 0
#define ONE_PLAYER 1
#define TWO_PLAYER 2

#define ROWS 16
#define COLUMNS 32
#define RESET true

#include "BLUETOOTH.h"
#include "PUCK.h"
#include "BALL.h"
#include "MATRIX.h"
#include "SCORE.h"

int mode = DEMO;
int difficultyLevel = 7;
int reset = 0;

void readInputs(PUCK &puckLeft, PUCK &puckRight) {
  puckLeft.dir = outputDirection(analogRead(12), analogRead(13));
  reset = digitalRead(13);
}

void setDifficultyLevel(int level) {
  difficultyLevel = level;
}

void setGameMode(int _mode) {
  mode = _mode;
}

void setUpScreen() {
  drawRow(0, whiteRGB);
  drawRow(ROWS - 1, whiteRGB);
  drawColumn(0, whiteRGB);
  drawColumn(COLUMNS - 1, whiteRGB);
}

void resetState(bool gameOver, PUCK &puckLeft, PUCK &puckRight, BALL &ball, SCORE &score) {
  black();
  setUpScreen();
  initializePucks(puckLeft, puckRight, puckLeft.rgb, puckRight.rgb);
  initializeBall(ball, ROWS, COLUMNS);
  if (gameOver) {
    initializeScore(score);
  }
  delay(50);
}

bool checkScores(SCORE &score, PUCK &puckLeft, PUCK &puckRight, BALL &ball) {
  if (score.player0 >= scoreToWin) {
    scrollText("Player 0 Wins!");
    resetState(RESET, puckLeft, puckRight, ball, score);
    return true;
  }
  if (score.player1 >= scoreToWin) {
    scrollText("Player 1 Wins!");
    resetState(RESET, puckLeft, puckRight, ball, score);
    return true;
  }  return false;
}

void printScores(SCORE &score, PUCK &puckLeft, PUCK &puckRight, BALL &ball) {
  char scoreString[6];
  scoreString[0] = score.player0 + '0';
  scoreString[1] = ' ';
  scoreString[2] = '-';
  scoreString[3] = ' ';
  scoreString[4] = score.player1 + '0';
  scoreString[5] = '\0';
  scrollText(scoreString);
  if (!checkScores(score, puckLeft, puckRight, ball)) {
    resetState(!RESET, puckLeft, puckRight, ball, score);
  }
}

void checkIfScored(PUCK &puckLeft, PUCK &puckRight, BALL &ball, int rows, int columns, SCORE &score) {
  int wallIntersection = checkWallIntersection(ball, rows, columns);
  if (wallIntersection != 0) {
    if (wallIntersection == 1) {
      score.player1 += 1;
      printScores(score, puckLeft, puckRight, ball);
    }
    if (wallIntersection == 2) {
      score.player0 += 1;
      printScores(score, puckLeft, puckRight, ball);
    }
    if (wallIntersection == 3 || wallIntersection == 4) {
      ball.velocity.y *= -1;
    }
  }
}


void updatePuckColors(BLUETOOTH &bt, PUCK &puckLeft, PUCK &puckRight) {
  if (!checkIfBlack(bt.puckLeftRGB)) {
    puckLeft.rgb.r = bt.puckLeftRGB.r;
    puckLeft.rgb.g = bt.puckLeftRGB.g;
    puckLeft.rgb.b = bt.puckLeftRGB.b;
  }
  if (!checkIfBlack(bt.puckRightRGB)) {
    puckRight.rgb.r = bt.puckRightRGB.r;
    puckRight.rgb.g = bt.puckRightRGB.g;
    puckRight.rgb.b = bt.puckRightRGB.b;
  }
}

void eraseOldPucks(PUCK &puckLeft, PUCK& puckRight) {
  drawPuck(puckLeft, blackRGB);
  drawPuck(puckRight, blackRGB);
}

void drawNewPucks(PUCK &puckLeft, PUCK &puckRight) {
  drawPuck(puckLeft, puckLeft.rgb);
  drawPuck(puckRight, puckRight.rgb);
}

void runPongGame(BLUETOOTH &bt, PUCK &puckLeft, PUCK & puckRight, BALL &ball, SCORE &score) {

  readInputs(puckLeft, puckRight);

  if (!reset) {
    resetState(RESET, puckLeft, puckRight, ball, score);
    delay(100);
  }
  //PONG GAME MODE
  readBluetooth(bt);
  updatePuckColors(bt, puckLeft, puckRight);

  if (checkScores(score, puckLeft, puckRight, ball)) {
    return;
  }

  drawBall(ball, true);
  updateBall(puckLeft, puckRight, ball);
  checkIfScored(puckLeft, puckRight, ball, ROWS, COLUMNS, score);
  drawBall(ball, false);
  eraseOldPucks(puckLeft, puckRight);

  switch (mode) {
    case DEMO:
      //DEMO MODE
      updateJSDirectionAI(puckLeft, ball, difficultyLevel);
      updateJSDirectionAI(puckRight, ball, difficultyLevel);
      break;
    case ONE_PLAYER:
      //ONE PLAYER
      updateJSDirection(puckLeft);
      updateJSDirectionAI(puckRight, ball, difficultyLevel);
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
