#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  game = new Game(3); // TODO
}

MainWindow::~MainWindow()
{
  delete game;
  delete ui;
}

void MainWindow::rollDice(){
  game->rollDice();
}

void MainWindow::placeMarker(){
  game->placeMarker();
}

void MainWindow::reverseTime(){

}

void MainWindow::placeDice(){

}

void MainWindow::endTurn(){
  game->endTurn();
}
