#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include "chessboard.h"

class Scene {
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
};

#endif	// SCENE_H
