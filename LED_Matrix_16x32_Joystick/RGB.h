#pragma once

struct RGB {
  int r;
  int g;
  int b;
};

RGB blackRGB={0,0,0};
RGB whiteRGB={255,255,255};

bool checkIfBlack(RGB &rgb){
	if(rgb.r != 0){
		return false;
	}
	else if(rgb.g != 0){
		return false;
	}
	else if(rgb.b != 0){
		return false;
	}	
	return true;	
}