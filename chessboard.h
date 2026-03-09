#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "chesspiece.h"
class ChessBoard {
   public:
    QGraphicsScene* scene;
    QGraphicsView* view;

    ChessBoard(QGraphicsScene* scene, QGraphicsView* view)
        : scene(scene), view(view) {}
    void drawChessboard();
    QPushButton* addToChessboard(ChessPiece* piece);

    int cellSize = 100;
};
#endif	// CHESSBOARD_H
