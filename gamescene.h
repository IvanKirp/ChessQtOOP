#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include "chessboard.h"
#include "mouseeventmediator.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

   public:
    QWidget* window = nullptr;
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();

    GameScene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
              QTableWidget* notation, QWidget* parent)
        : scene(scene),
          view(view),
          newBoard(newBoard),
          notation(notation),
          window(parent) {
        giveUpButton = new QPushButton("сдаться", window);
        giveUpButton->hide();
        drawButton = new QPushButton("ничья", window);
        drawButton->hide();
        homeButton = new QPushButton("Выйти в главное меню", window);
        homeButton->hide();
        mouseEventMediator->setScene(this);
        mouseEventMediator->setConnection();
    }

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

   signals:
    void mousePressedToMove();
    void mousePressedToChoose();

   public slots:
    void showStopButtons();
    void hideStopButtons();
};

#endif	// GAMESCENE_H
