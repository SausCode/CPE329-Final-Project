#pragma once

#define JSMAX 600
#define JSMIN 400

int xDirection(int x) {
  /*
     0 = WEST
     1 = NEUTRAL
     2 = EAST
  */

  if (x < JSMIN) {
    //X is WEST
    return 0;
  }

  else if (x > JSMAX) {
    //X is EAST
    return 2;
  }

  else {
    //X is NEUTRAL
    return 1;
  }

}

int yDirection(int y) {
  /*
     0 = SOUTH
     1 = NEUTRAL
     2 = NORTH
  */

  if (y < JSMIN) {
    //Y is SOUTH
    return 0;
  }

  else if (y > JSMAX) {
    //Y is NORTH
    return 2;
  }

  else {
    //Y in NEUTRAL
    return 1;
  }

}

int outputDirection(int x, int y) {
  int direction = 1;
  /*
     0 = No Direction
     1 = North
     2 = NorthEast
     3 = East
     4 = SouthEast
     5 = South
     6 = SouthWest
     7 = West
     8 = NorthWest
  */

  int xDir = xDirection(x);
  int yDir = yDirection(y);

  if (xDir == 0) {
    if (yDir == 0) {
      return 6;
    }
    else if (yDir == 1) {
      return 7;
    }
    else if (yDir == 2) {
      return 8;
    }
  }

  else if (xDir == 1) {
    if (yDir == 0) {
      return 5;
    }
    else if (yDir == 1) {
      return 0;
    }
    else if (yDir == 2) {
      return 1;
    }
  }

  else if (xDir == 2) {
    if (yDir == 0) {
      return 4;
    }
    else if (yDir == 1) {
      return 3;
    }
    else if (yDir == 2) {
      return 2;
    }
  }
  return direction;
}