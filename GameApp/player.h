#ifndef PLAYER_H
#define PLAYER_H
#include "tools.h"
#include "common.h"
#include <QColor>

class Player
{
private:
  int *nTools;
  QColor color;
  double cash;
  double bitcoin;
  int playernum;
  int pos;
  const QColor PlayerColor[MAXPLAYER] = {QColor(255, 0, 0), QColor(255, 255, 0), QColor(0, 0, 255), QColor(0, 255, 0)};
  QColor getColor(int playernum);

public:
  friend class Game;
  Player(int _playernum);
  ~Player();
};

#endif // PLAYER_H
