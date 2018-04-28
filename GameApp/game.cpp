#include "game.h"

Game::Game(int _nPlayer):nPlayer(_nPlayer)
{
  grids = new Grid[NGRID];

  //set map
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
  excgRate = 10;

  dice = new Dice;
}

Game::~Game(){
  delete []grids;
  for(int i = 0; i < nPlayer; ++i){
    delete players[i];
  }
  delete []players;
  delete dice;
}

void Game::rollDice(){
  int rollres = dice->roll();
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
  if(currPlayer->cash < 0){
    currPlayer->cash = 0;
  }
  currPlayer->bitcoin += grids[targetPos].gamma;
  if(currPlayer->bitcoin < 0){
    currPlayer->bitcoin = 0;
  }
}

void Game::endTurn(){
  ++whoseTurn;
  if(whoseTurn >= nPlayer){
    whoseTurn = 0;
    ++currentTurn;
    if(currentTurn >= MAXTURN){
      exit();
    }
  }
}

void Game::placeMarker(){
  Player *currPlayer = players[whoseTurn];
  if(currPlayer->nTools[Tools::ButterflyMark] == 0){
    return;
  }
  currPlayer->nTools[Tools::ButterflyMark]--;
  //send snapshot
  ButterflyMarker b(whoseTurn, currentTurn, currPlayer->pos);
  grids[currPlayer->pos].insertButterfly(b);
}

void Game::reverseTime(int gridNum){
  Player *currPlayer = players[whoseTurn];
  if(grids[gridNum].hasHisMarker(whoseTurn) != nullptr && currPlayer->nTools[Tools::TimeJump] > 0){
    // reverse time
    // query with grids[gridNum].hasHisMarker(whoseTurn)->tag;
    // apply snapshot
  }
}

void Game::placeDice(int num){
  Player *currPlayer = players[whoseTurn];
  if(currPlayer->nTools[Tools::ControlledDice] == 0){
    return;
  }
  currPlayer->nTools[Tools::ControlledDice]--;
  //send controlled dice
}

void Game::exit(){
  //TODO
}

QString Game::toJSON(){
  QJsonObject res;
  res.insert("Rate", QJsonValue(QString::number(excgRate)));
  QJsonArray array;
  for(int i = 0; i < nPlayer; ++i){
    QJsonObject player;
    player.insert("Position", players[i]->pos);
    player.insert("Cash", players[i]->cash);
    player.insert("Bitcoin", players[i]->bitcoin);
    array.insert(array.size(), QJsonValue(player));
  }
  res.insert("Players", array);
  QJsonArray array2;
  for(int i = 0; i < NGRID; ++i){
    for(int j = 0; j < grids[i].butterflies.size(); ++j){
      QJsonObject marker;
      marker.insert("Position", grids[i].butterflies[j].pos);
      marker.insert("Round", grids[i].butterflies[j].round);
      marker.insert("Owner", grids[i].butterflies[j].whose);
      array2.insert(array2.size(), marker);
    }
  }
  res.insert("Butterflies", array2);
  QJsonDocument doc(res);
  QString str(doc.toJson(QJsonDocument::Compact));
  return str;
}

void Game::fromJSON(QString json){
  QByteArray barray;
  barray.append(json);
  QJsonDocument doc = QJsonDocument::fromJson(barray);
  QJsonObject obj = doc.object();
  excgRate = obj.value("Rate").toDouble();
  for(int i = 0; i < nPlayer; ++i){
    QJsonObject player = obj.value("Players").toArray().at(i).toObject();
    players[i]->pos = player.value("Position").toInt();
    players[i]->cash = player.value("Cash").toDouble();
    players[i]->bitcoin = player.value("Bitcoin").toDouble();
  }
  QJsonArray array = obj.value("Butterflies").toArray();
  for(int i = 0; i < NGRID; ++i){
    grids[i].butterflies.clear();
  }
  for(int i = 0; i < array.size(); ++i){
    int pos = array.at(i).toObject().value("Position").toInt();
    int whose = array.at(i).toObject().value("Owner").toInt();
    int round = array.at(i).toObject().value("Round").toInt();
    grids[pos].butterflies.append(ButterflyMarker(whose, round, pos));
  }
}
