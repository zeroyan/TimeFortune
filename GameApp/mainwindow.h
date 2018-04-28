#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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
  void updateUI();

private:
  Ui::MainWindow *ui;
  Game *game;
  QLabel **butterflyLabel;

public slots:
  void rollDice();
  void placeMarker();
  void reverseTime();
  void placeDice_1();
  void placeDice_2(int arg);
  void endTurn();
};

#endif // MAINWINDOW_H
