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
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();

    GameScene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
              QTableWidget* notation)
        : scene(scene), view(view), newBoard(newBoard), notation(notation) {
        mouseEventMediator->setScene(this);
        mouseEventMediator->setConnection();
    }

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

   signals:
    void mousePressed();
};

#endif	// GAMESCENE_H
