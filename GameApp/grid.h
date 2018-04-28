#ifndef GRID_H
#define GRID_H
#include <QVector>
#include <butterflymarker.h>

class Grid
{
  bool isExchange;
  bool hasMarker; // event determined
  double alpha; // excgRate *= alpha
  double beta;  // cash += beta
  double gamma; // bitcoin += gamma
  bool isStart; // add 1 controlled dice
  QVector<ButterflyMarker> butterflies;

public:
  friend class Game;
  Grid();
  void insertButterfly(ButterflyMarker &b);
  ButterflyMarker * hasHisMarker(int playernum);
  static void returnXY(int pos, int player, int &x, int &y);
};

#endif // GRID_H
