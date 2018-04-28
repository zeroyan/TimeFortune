#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSignalMapper>
#include <QBitmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  game = new Game(3); // TODO
  qDebug() << game->toJSON();
  /*
  QIcon icon(":/new/icon/pictures/grid1.png");
  ui->grid01->setMinimumSize(QSize(130, 130));
  ui->grid01->setMaximumSize(QSize(130, 130));
  ui->grid01->setIcon(icon);
  ui->grid01->setIconSize(QSize(125, 125));
  */
  if(game->nPlayer < 4){
    ui->player4_bg->hide();
    ui->player4_tx1->hide();
    ui->player4_tx2->hide();
    ui->player4_tx3->hide();
    ui->player4_tx4->hide();
    ui->player4_tx5->hide();
    ui->player4_tx6->hide();
    ui->player4_tx7->hide();
  }
  if(game->nPlayer < 3){
    ui->player3_bg->hide();
    ui->player3_tx1->hide();
    ui->player3_tx2->hide();
    ui->player3_tx3->hide();
    ui->player3_tx4->hide();
    ui->player3_tx5->hide();
    ui->player3_tx6->hide();
    ui->player3_tx7->hide();
  }
  if(game->nPlayer < 2){
    ui->player2_bg->hide();
    ui->player2_tx1->hide();
    ui->player2_tx2->hide();
    ui->player2_tx3->hide();
    ui->player2_tx4->hide();
    ui->player2_tx5->hide();
    ui->player2_tx6->hide();
    ui->player2_tx7->hide();
  }

  ui->bt_1->hide();
  ui->bt_2->hide();
  ui->bt_3->hide();
  ui->bt_4->hide();
  ui->bt_endturn->setEnabled(false);
  connect(ui->dice, SIGNAL(clicked(bool)), this, SLOT(rollDice()));
  connect(ui->bt_endturn, SIGNAL(clicked(bool)), this, SLOT(endTurn()));
  connect(ui->bt_butterfly, SIGNAL(clicked(bool)), this, SLOT(placeMarker()));
  connect(ui->bt_timerecall, SIGNAL(clicked(bool)), this, SLOT(reverseTime()));
  connect(ui->bt_remotedice, SIGNAL(clicked(bool)), this, SLOT(placeDice_1()));
  butterflyLabel = new QLabel **[game->nPlayer];
  for(int i = 0; i < game->nPlayer; ++i){
    butterflyLabel[i] = new QLabel *[NGRID];
    for(int j = 0; j < NGRID; ++j){
      butterflyLabel[i][j] = new QLabel(this);
      QPixmap pixmap(":/new/icon/butterfly1.png");
      butterflyLabel[i][j]->setPixmap(pixmap);
      butterflyLabel[i][j]->setMask(pixmap.mask());
      int x, y;
      Grid::returnXYButterfly(j, i, x, y);
      qDebug() << "Coord: " << x << " " << y;
      butterflyLabel[i][j]->setGeometry(x, y, 41, 31);
    }
  }
  updateUI();
  this->update();
}
MainWindow::~MainWindow()
{
  delete game;
  for(int i = 0; i < game->nPlayer; ++i){
    for(int j = 0; j < NGRID; ++j){
      delete butterflyLabel[i][j];
    }
    delete[] butterflyLabel[i];
  }
  delete []butterflyLabel;
  delete ui;
}

void MainWindow::updateUI(){
  ui->exchange_tx->setText(QString("1 Time coin = $")+QString::number(game->excgRate, 'f', 2));
  ui->player1_tx2->hide();
  QPalette pe;
  pe.setColor(QPalette::WindowText, Qt::black);
  ui->player1_tx1->setPalette(pe);
  ui->player2_tx1->setPalette(pe);
  ui->player3_tx1->setPalette(pe);
  ui->player4_tx1->setPalette(pe);
  pe.setColor(QPalette::WindowText, Qt::red);
  ui->player1_tx1->setText(QString("Player 1"));
  switch(game->whoseTurn){
    case 0:
      ui->player1_tx1->setPalette(pe);
      break;
    case 1:
      ui->player2_tx1->setPalette(pe);
      break;
    case 2:
      ui->player3_tx1->setPalette(pe);
      break;
    case 3:
      ui->player4_tx1->setPalette(pe);
      break;
  }
  ui->player2_tx1->setText(QString("Player 2"));
  ui->player3_tx1->setText(QString("Player 3"));
  ui->player4_tx1->setText(QString("Player 4"));
  ui->player1_tx3->setText(QString("现金: $")+QString::number(game->players[0]->cash, 'f', 2));
  ui->player1_tx4->setText(QString("Time coin: ")+QString::number(game->players[0]->bitcoin, 'f', 2));
  ui->player1_tx5->setText(QString("蝴蝶印记: ")+QString::number(game->players[0]->nTools[Tools::ButterflyMark]));
  ui->player1_tx6->setText(QString("时光回溯: ")+QString::number(game->players[0]->nTools[Tools::TimeJump]));
  ui->player1_tx7->setText(QString("遥控骰子: ")+QString::number(game->players[0]->nTools[Tools::ControlledDice]));
  if(game->nPlayer > 1){
    ui->player2_tx2->hide();
    ui->player2_tx3->setText(QString("现金: $")+QString::number(game->players[1]->cash, 'f', 2));
    ui->player2_tx4->setText(QString("Time coin: ")+QString::number(game->players[1]->bitcoin, 'f', 2));
    ui->player2_tx5->setText(QString("蝴蝶印记: ")+QString::number(game->players[1]->nTools[Tools::ButterflyMark]));
    ui->player2_tx6->setText(QString("时光回溯: ")+QString::number(game->players[1]->nTools[Tools::TimeJump]));
    ui->player2_tx7->setText(QString("遥控骰子: ")+QString::number(game->players[1]->nTools[Tools::ControlledDice]));
    if(game->nPlayer > 2){
      ui->player3_tx2->hide();
      ui->player3_tx3->setText(QString("现金: $")+QString::number(game->players[2]->cash, 'f', 2));
      ui->player3_tx4->setText(QString("Time coin: ")+QString::number(game->players[2]->bitcoin, 'f', 2));
      ui->player3_tx5->setText(QString("蝴蝶印记: ")+QString::number(game->players[2]->nTools[Tools::ButterflyMark]));
      ui->player3_tx6->setText(QString("时光回溯: ")+QString::number(game->players[2]->nTools[Tools::TimeJump]));
      ui->player3_tx7->setText(QString("遥控骰子: ")+QString::number(game->players[2]->nTools[Tools::ControlledDice]));
      if(game->nPlayer > 3){
        ui->player4_tx2->hide();
        ui->player4_tx3->setText(QString("现金: $")+QString::number(game->players[3]->cash, 'f', 2));
        ui->player4_tx4->setText(QString("Time coin: ")+QString::number(game->players[3]->bitcoin, 'f', 2));
        ui->player4_tx5->setText(QString("蝴蝶印记: ")+QString::number(game->players[3]->nTools[Tools::ButterflyMark]));
        ui->player4_tx6->setText(QString("时光回溯: ")+QString::number(game->players[3]->nTools[Tools::TimeJump]));
        ui->player4_tx7->setText(QString("遥控骰子: ")+QString::number(game->players[3]->nTools[Tools::ControlledDice]));
      }
    }
  }
  int x, y;
  Grid::returnXY(game->players[0]->pos, 0, x, y);
  ui->avatar1->setGeometry(x, y, 31, 31);
  Grid::returnXY(game->players[1]->pos, 1, x, y);
  ui->avatar2->setGeometry(x, y, 31, 31);
  Grid::returnXY(game->players[2]->pos, 2, x, y);
  ui->avatar3->setGeometry(x, y, 31, 31);

  for(int i = 0; i < NGRID; ++i){
    for(int j = 0; j < game->nPlayer; ++j){
      if(game->grids[i].hasHisMarker(j)){
        qDebug() << i << " " << j << " SHOW";
        butterflyLabel[j][i]->show();
      }
      else{
        qDebug() << i << " " << j << " HIDE";
        butterflyLabel[j][i]->show();
      }
    }
  }
}

void MainWindow::rollDice(){
  qDebug() << "Roll dice";
  ui->dice->setEnabled(false);
  ui->bt_endturn->setEnabled(true);
  ui->bt_butterfly->setEnabled(false);
  game->rollDice();
  updateUI();
  update();
}

void MainWindow::placeMarker(){
  qDebug() << "Place butterfly marker";
  game->placeMarker();
  updateUI();
  update();
}

void MainWindow::reverseTime(){
  qDebug() << "Reverse time";
  updateUI();
  update();
}

void MainWindow::placeDice_1(){
  ui->bt_1->show();
  ui->bt_2->show();
  ui->bt_3->show();
  ui->bt_4->show();
  QSignalMapper *signalMapper = new QSignalMapper(this);
  connect(ui->bt_1, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
  connect(ui->bt_2, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
  connect(ui->bt_3, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
  connect(ui->bt_4, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

  signalMapper->setMapping(ui->bt_1, 1);
  signalMapper->setMapping(ui->bt_2, 2);
  signalMapper->setMapping(ui->bt_3, 3);
  signalMapper->setMapping(ui->bt_4, 4);

  connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(placeDice_2(int)));
}

void MainWindow::placeDice_2(int arg){
  qDebug() << "Place dice";
  disconnect(ui->bt_1, 0, 0, 0);
  disconnect(ui->bt_2, 0, 0, 0);
  disconnect(ui->bt_3, 0, 0, 0);
  disconnect(ui->bt_4, 0, 0, 0);
  ui->bt_1->hide();
  ui->bt_2->hide();
  ui->bt_3->hide();
  ui->bt_4->hide();
  game->placeDice(arg);
  updateUI();
  update();
}

void MainWindow::endTurn(){
  qDebug() << "End turn";
  ui->bt_endturn->setEnabled(false);
  ui->bt_butterfly->setEnabled(true);
  ui->dice->setEnabled(true);
  game->endTurn();
  updateUI();
  update();
}
