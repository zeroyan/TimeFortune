#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  Game *game;

public slots:
  void rollDice();
  void placeMarker();
  void reverseTime();
  void placeDice();
  void endTurn();
};

#endif // MAINWINDOW_H
