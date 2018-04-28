#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include "player.h"
#include "dice.h"

class Game
{
private:
  Grid *grids;
  Player **players;
  int nPlayer;
  int whoseTurn;
  int currentTurn;
  double excgRate;  // bitcoin = excgRate * cash
  Dice dice;
public:
  Game(int _nPlayer);
  ~Game();
  void rollDice();
  void useTool(Tools tool);
};

#endif // GAME_H
