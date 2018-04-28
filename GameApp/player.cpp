#include "player.h"

Player::Player(int _playernum): playernum(_playernum)
{
  nTools = new int [Tools::TOOLNUM];
  // init to 0
  for(int i = 0; i < Tools::TOOLNUM; ++i){
    nTools[i] = 0;
  }

  // init tools
  nTools[Tools::ButterflyMark] = 3;
  nTools[Tools::TimeJump] = 1;
  nTools[Tools::ControlledDice] = 1;

  color = getColor(playernum);
  cash = INITCASH;
  bitcoin = 0;
  pos = 0;
}

QColor Player::getColor(int playernum){
  Q_ASSERT(playernum < MAXPLAYER);
  return PlayerColor[playernum];
}

Player::~Player(){
  delete []nTools;
}
