#ifndef BUTTERFLYMARKER_H
#define BUTTERFLYMARKER_H
#include <QString>

class ButterflyMarker
{
public:
  int round;
  QString tag;  // 由区块链给出
  int pos;
  int whose;
  ButterflyMarker(int _whose, int _round, int _pos);
  ButterflyMarker(){
    round = 0;
    whose = 0;
    pos = 0;
  }
};

#endif // BUTTERFLYMARKER_H
