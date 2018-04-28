#ifndef GRID_H
#define GRID_H

class Grid
{
  bool isExchange;
  bool hasMarker; // event determined
  double alpha; // excgRate *= alpha
  double beta;  // cash += beta
  double gamma; // bitcoin += gamma
  bool isStart; // add 1 controlled dice

public:
  friend class Game;
  Grid();
};

#endif // GRID_H
