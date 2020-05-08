#include <iostream>
#include <fstream>
#include "Game.hpp"

int main () {

  srand(time(0));

  const int GAMES_CNT = 5;
  Game **g = new Game*[GAMES_CNT];

  for (int gameCnt = 0; gameCnt < GAMES_CNT; ++ gameCnt) {
    g[gameCnt] = new Game();
    g[gameCnt]->run();
    delete g[gameCnt];
  }

  delete[] g;
}
