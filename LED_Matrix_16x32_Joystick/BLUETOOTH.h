#pragma once

#include "RGB.h"

struct BLUETOOTH {
  RGB puckLeftRGB;
  RGB puckRightRGB;
};

int state;

unsigned int readBtUnsignedInt(BLUETOOTH &bt) {
  return Serial1.read();
}

void readBluetooth(BLUETOOTH &bt) {
  int index = 0;
  //0 : LEFT
  //1 : RIGHT
  int side = 0;
  while (Serial1.available() > 0) {
    switch (index) {
      case 0:
        side = readBtUnsignedInt(bt);
        index++;
      case 1:
        if (side == 0) {
          bt.puckLeftRGB.r = readBtUnsignedInt(bt);
        }
        else {
          bt.puckRightRGB.r = readBtUnsignedInt(bt);
        }
        index++;
        break;
      case 2:
        if (side == 0) {
          bt.puckLeftRGB.g = readBtUnsignedInt(bt);
        }
        else {
          bt.puckRightRGB.g = readBtUnsignedInt(bt);
        }
        index++;
        break;
      case 3:
        if (side == 0) {
          bt.puckLeftRGB.b = readBtUnsignedInt(bt);
        }
        else {
          bt.puckRightRGB.b = readBtUnsignedInt(bt);
        }
        index = 0;
        break;
    }
  }
}
