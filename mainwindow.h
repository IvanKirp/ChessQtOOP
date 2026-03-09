#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bishop.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "classicgame.h"
#include "gamemode.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "scene.h"

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

    QList<QPushButton*> allChessPieceButtons;
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene);
    ChessBoard* newBoard = new ChessBoard(scene, view);
    QTableWidget* notation;
    QPushButton *startButton, *readButton, *exitButton;
    void startWindow();
    void drawScene();

   private:
    Ui::MainWindow* ui;
};
#endif	// MAINWINDOW_H
