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

  players = new Player *[nPlayer];
  for(int i = 0; i < nPlayer; ++i){
    players[i] = new Player(i);
  }
  whoseTurn = 0;
  currentTurn = 0;
  excgRate = 1;
}

Game::~Game(){
  delete []grids;
  for(int i = 0; i < nPlayer; ++i){
    delete players[i];
  }
  delete []players;
}

void Game::rollDice(){
  int rollres = dice.roll();
  Player *currPlayer = players[whoseTurn];
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
    //TODO: ask for exchange amount
  }
  else if(passStart){
    currPlayer->nTools[Tools::ControlledDice]++;
  }



  //arrive at target position
  int targetPos = currPlayer->pos = (currPos + rollres) % NGRID;
  if(!grids[targetPos].hasMarker){
    //TODO: ask blockchain for event and record it
    grids[targetPos].hasMarker = true;
  }

  //apply the event
  excgRate *= grids[targetPos].alpha;
  currPlayer->cash += grids[targetPos].beta;
  currPlayer->bitcoin += grids[targetPos].gamma;
}
