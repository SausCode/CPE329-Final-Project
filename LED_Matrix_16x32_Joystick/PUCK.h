#pragma once

#define ROWS 16
#define COLUMNS 32

#define MIN_LEFT_X 2
#define MAX_LEFT_X 5
#define MIN_RIGHT_X 26
#define MAX_RIGHT_X 29

#define STARTING_PUCK_LEFT_X 3
#define STARTING_PUCK_LEFT_Y ROWS/2
#define STARTING_PUCK_RIGHT_X 28
#define STARTING_PUCK_RIGHT_Y ROWS/2

#include "BALL.h"
#include "RGB.h"

struct PUCK {
  int x;
  int y;
  int width;
  int height;
  //0 = LEFT, 1 = RIGHT
  int side;
  int dir;
  RGB rgb;
};

void setStartupPuckColors(PUCK &puckLeft, PUCK &puckRight){
  puckLeft.rgb.r = 0;
  puckLeft.rgb.g = 3;
  puckLeft.rgb.b = 0;
  puckRight.rgb.r = 0;
  puckRight.rgb.g = 3;
  puckRight.rgb.b = 0;
}

void initializePucks(PUCK &puckLeft, PUCK &puckRight, RGB rgbLeft, RGB rgbRight) {
  puckLeft = {STARTING_PUCK_LEFT_X, STARTING_PUCK_LEFT_Y - 1, 1, 3, 0, 0, rgbLeft.r, rgbLeft.g, rgbLeft.b};
  puckRight = {STARTING_PUCK_RIGHT_X, STARTING_PUCK_RIGHT_Y - 1, 1, 3, 1, 0, rgbRight.r, rgbRight.g, rgbRight.b};
}

void puckNorth(PUCK &puck) {
  if (puck.y < 2)
    return;
  puck.y--;
}

void puckSouth(PUCK &puck) {
  if (puck.y > ROWS - (puck.height + 2))
    return;
  puck.y++;
}

void puckEast(PUCK &puck) {
  if (puck.x > MAX_LEFT_X) {
    return;
  }
  //puck.x++;
}

void puckWest(PUCK &puck) {
  if (puck.side == 0) {
    //LEFT PUCK
    if (puck.x < MIN_LEFT_X) {
      return;
    }
  }
  else {
    //RIGHT PUCK
    if (puck.x < COLUMNS - 6) {
      return;
    }
  }
  //puck.x--;
}

bool checkPuckIntersectionY(PUCK &puckLeft, PUCK &puckRight, BALL ball) {
  for (int h = 0; h < puckLeft.height; h++) {
    if (ball.y == puckLeft.y + h) {
      return true;
    }
  }
  for (int h = 0; h < puckRight.height; h++) {
    if (ball.y == puckRight.y + h) {
      return true;
    }
  }
  return false;
}

//RETURNS 0 if NO INTERSECTION
//RETURNS 1 if INTERSECTS LEFT PUCK
//RETURNS 2 if INTERSECTS RIGHT PUCK
int checkPuckIntersection(PUCK &puckLeft, PUCK &puckRight, BALL ball) {
  if (checkPuckIntersectionY(puckLeft, puckRight, ball) && ball.x == puckLeft.x) {
    ball.x += 1;
    return 1;
  }
  else if (checkPuckIntersectionY(puckLeft, puckRight, ball) && ball.x == puckRight.x) {
    return 2;
  }
  return 0;
}

void updateBall(PUCK &puckLeft, PUCK &puckRight, BALL &ball) {
  if (checkPuckIntersection(puckLeft, puckRight, ball) != 0) {
    ball.velocity.x *= -1;
    if (ball.velocity.y == 0) {
      ball.velocity.y = 1;
    }
    int r = random(0, 2);
    if (r == 0) {
      ball.velocity.y = ball.velocity.y ;
    }
    else {
      ball.velocity.y *= -1;
    }
  }

  ball.x += ball.velocity.x;
  ball.y += ball.velocity.y;
}

void updateJSDirection(PUCK &puck) {
  switch (puck.dir) {
    case 0:
      //NEUTRAL
      break;
    case 1:
      //NORTH
      puckNorth(puck);
      break;
    case 2:
      //NORTHEAST
      puckNorth(puck);
      puckEast(puck);
      break;
    case 3:
      //EAST
      puckEast(puck);
      break;
    case 4:
      //SOUTHEAST
      puckSouth(puck);
      puckEast(puck);
      break;
    case 5:
      //SOUTH
      puckSouth(puck);
      break;
    case 6:
      //SOUTHWEST
      puckSouth(puck);
      puckWest(puck);
      break;
    case 7:
      //WEST
      puckWest(puck);
      break;
    case 8:
      //NORTHWEST
      puckNorth(puck);
      puckWest(puck);
      break;
  }
}

void updateJSDirectionAI(PUCK &puck, BALL &ball, int DIFFICULTY_LEVEL) {
  int r = random(0, DIFFICULTY_LEVEL);
  if (r != 0) {
    if (ball.y < puck.y) {
      puckNorth(puck);
    }
    else {
      puckSouth(puck);
    }
  }
}
