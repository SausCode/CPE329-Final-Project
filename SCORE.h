#pragma once

#define SCORE_TO_WIN 7

struct SCORES {
  int player0;
  int player1;
};

int scoreToWin = SCORE_TO_WIN;

void initializeScore(SCORES &score) {
  score.player0 = 0;
  score.player1 = 0;
}

void setScoreLimit(int score) {
  scoreToWin = score;
}
