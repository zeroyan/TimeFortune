#include "player.h"

Player::Player(int _playernum): playernum(_playernum)
{
  nTools = new int [Tools::TOOLNUM];
  // 统一置零
  for(int i = 0; i < Tools::TOOLNUM; ++i){
    nTools[i] = 0;
  }

  //初始道具
  nTools[Tools::ButterflyMark] = 3;
  nTools[Tools::TimeJump] = 1;
  nTools[Tools::ControlledDice] = 1;

  color = g_getColor(playernum);
  cash = INITCASH;
  bitcoin = 0;
  pos = 0;
}

Player::~Player(){
  delete []nTools;
}
