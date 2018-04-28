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

public:
  Player();
  ~Player();
};

#endif // PLAYER_H
