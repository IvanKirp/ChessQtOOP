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

class Scene : public QGraphicsScene {
    Q_OBJECT

   public:
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;

    Scene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
          QTableWidget* notation)
        : scene(scene), view(view), newBoard(newBoard), notation(notation) {}

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif	// SCENE_H
