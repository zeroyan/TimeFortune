#ifndef GAME_H
#define GAME_H
#include "grid.h"
#include "player.h"
#include "dice.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>


class Game
{
private:
  Grid *grids;
  Player **players;
  int nPlayer;
  int whoseTurn;
  int currentTurn;
  double excgRate;  // bitcoin = excgRate * cash
  Dice *dice;
public:
  explicit Game(int _nPlayer);
  ~Game();
  void rollDice();
  void placeMarker();
  void reverseTime(int);
  void placeDice(int);
  void endTurn();
  void exit();
  QString toJSON();
  void fromJSON(QString json);
};

#endif // GAME_H
