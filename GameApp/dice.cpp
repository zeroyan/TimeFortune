#include "dice.h"
#include <ctime>

Dice::Dice()
{
  qsrand((unsigned int)time(NULL));
}

int Dice::roll(){
  return 1 + qrand()%4;
}
