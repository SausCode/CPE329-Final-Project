#pragma once
#include "VELOCITY.h"
struct BALL {
  int x;
  int y;
  VELOCITY velocity;
};

VELOCITY ballVelocity;

void initializeBall(BALL &ball, int ROWS, int COLUMNS) {
  int r = random(0, 2);
  if (r == 0) {
    ballVelocity = {1, 1};
  }
  else {
    ballVelocity = { -1, 1};
  }
  ball = {(COLUMNS / 2) - 1, ROWS / 2, ballVelocity};
}

//RETURNS 0 if HITS NO WALL
//RETURNS 1 if HITS LEFT WALL
//RETURNS 2 if HITS RIGHT WALL
//RETURNS 3 if HITS TOP WALL
//RETURNS 4 if HITS Bottom WALL
int checkWallIntersection(BALL &ball, int ROWS, int COLUMNS) {
  if (ball.x == 0) {
    return 1;
  }
  else if (ball.x == COLUMNS) {
    return 2;
  }
  else if (ball.y == 1) {
    return 3;
  }
  else if (ball.y == ROWS - 2) {
    return 4;
  }
  return 0;
}