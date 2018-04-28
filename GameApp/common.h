#ifndef COMMON_H
#define COMMON_H
#include <QColor>
const int MAXPLAYER = 4;
const int MINPLAYER = 2;
const QColor PlayerColor[MAXPLAYER] = {QColor(255, 0, 0), QColor(255, 255, 0), QColor(0, 0, 255), QColor(0, 255, 0)};
const int INITCASH = 10000;
const int MAXTURN = 8;
const int NGRID = 20;
const int NEVENT = 25;

QColor g_getColor(int playernum){
  Q_ASSERT(playernum < MAXPLAYER);
  return PlayerColor[playernum];
}

int g_roll(){
  // TODO
}
#endif // COMMON_H
