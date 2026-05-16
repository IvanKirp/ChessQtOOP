#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bishop.h"
#include "chessboard.h"
#include "chessnotation.h"
#include "chesspiece.h"
#include "classicgame.h"
#include "customsetupmode.h"
#include "fischerchess.h"
#include "gamemode.h"
#include "gamescene.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include <QAbstractButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPointF>
#include <QPushButton>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    int cellSize = 100;
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene);
    ChessBoard* newBoard = new ChessBoard(scene, view, cellSize);
    QTableWidget* notation = new QTableWidget(this);
    ChessNotation* chessNotation = new ChessNotation(notation);
    QPushButton *startButton, *readButton, *exitButton;
    QList<QPushButton*> allGameModeButtons;
    QList<GameMode*> allGameModes;
    void startWindow();
    void chooseGameMode();
    void drawScene(GameMode* gamemode);

   private:
    Ui::MainWindow* ui;
};
#endif	// MAINWINDOW_H
