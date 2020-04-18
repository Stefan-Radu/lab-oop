#include <iostream>
#include <fstream>
#include "Game.hpp"

int main () {

  srand(time(0));

  const int GAMES_CNT = 7;
  Game **g = new Game*[GAMES_CNT];

  for (int gameCnt = 0; gameCnt < GAMES_CNT; ++ gameCnt) {

    int preyPerc = rand() % 10 + 1;
    int predatorPerc = rand() % 10 + 1;
    int preyMaxHealth = rand() % 50 + 1;
    int preyHealthTic = rand() % 5 + 1;
    int predatorMaxHealth = rand() % 50 + 1;
    int predatorHealthTic = rand() % 5 + 1;

    g[gameCnt] = new Game(preyPerc, predatorPerc,
                    preyMaxHealth, preyHealthTic,
                    predatorMaxHealth, predatorHealthTic);

    std::cerr << "\nInitialized game no. " << gameCnt << " with:\n";
    std::cerr << "Prey percentage: " << predatorPerc << " / " << Game::CHANCE_MODULO << '\n';
    std::cerr << "Predator percentage: " << predatorPerc << " / " << Game::CHANCE_MODULO << '\n';
    std::cerr << "Maximum health of prey: " << preyMaxHealth <<  '\n';
    std::cerr << "Health tic of prey (+- 1): " << preyHealthTic <<  '\n';
    std::cerr << "Maximum health of predator: " << predatorMaxHealth <<  '\n';
    std::cerr << "Health tic of predator (+- 1): " << predatorHealthTic <<  '\n';

    g[gameCnt] -> run();
    delete g[gameCnt];
  }

  delete[] g;

  // TODO change game logic for more performance - creatures in sepparate arrays
  // TODO remake redame 
  // TODO git tags
  // TODO git release notes
}
