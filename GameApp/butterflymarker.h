#ifndef BUTTERFLYMARKER_H
#define BUTTERFLYMARKER_H
#include <QString>

class ButterflyMarker
{
private:
  int round;
  QString tag;  // 由区块链给出
public:
  ButterflyMarker(int _round);
};

#endif // BUTTERFLYMARKER_H
