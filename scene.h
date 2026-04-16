#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include "chessboard.h"
#include "mouseeventmediator.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

   public:
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();

    Scene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
          QTableWidget* notation)
        : scene(scene), view(view), newBoard(newBoard), notation(notation) {}

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

   signals:
    void mousePressed();
};

#endif	// SCENE_H
