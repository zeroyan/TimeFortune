#ifndef GRID_H
#define GRID_H


class Grid
{
  bool isExchange;
  bool hasMarker; // 事件已确定
  double alpha; // excgRate *= alpha
  double beta;  // cash += beta
  double gamma; // bitcoin += gamma
  bool isStart; // 送道具

public:
  Grid();
};

#endif // GRID_H
