#include "game.h"

Game::Game(int _nPlayer): nPlayer(_nPlayer)
{
  grids = new Grid[NGRID];

  //设置地图
  grids[0].isStart = true;
  for(int i = 0; i < NGRID; ++i){
    if(i % 5 == 0){
      grids[i].isExchange = true;
    }
  }

  players = new Player[nPlayer];
  whoseTurn = 0;
  currentTurn = 0;
  excgRate = 1;
}

Game::~Game(){
  delete []grids;
  delete []players;
}

void Game::rollDice(){
  int rollres = dice.roll();
  Player *currPlayer = &players[whoseTurn];
  int currPos = currPlayer->pos;

  bool passExchange = false;
  bool passStart = false;
  for(int i = 1; i <= rollres; ++i){
    if(grids[(currPos + i) % NGRID].isExchange){
      passExchange = true;
      break;
    }
    else if(grids[(currPos + i) % NGRID].isStart){
      passStart = true;
      break;
    }
  }

  if(passExchange){
    //TODO: 询问兑换数量
  }
  else if(passStart){
    currPlayer->nTools[Tools::ControlledDice]++;
  }



  //到达目标位置
  int targetPos = currPlayer->pos = (currPos + rollres) % NGRID;
  if(!grids[targetPos].hasMarker){
    //TODO: 向区块链询问事件并记录
    grids[targetPos].hasMarker = true;
  }

  //应用事件
  excgRate *= grids[targetPos].alpha;
  currPlayer->cash += grids[targetPos].beta;
  currPlayer->bitcoin += grids[targetPos].gamma;
}
