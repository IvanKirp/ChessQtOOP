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
    QList<QGraphicsEllipseItem*> circle;
    int cellSize = 100;

    ChessBoard(QGraphicsScene* scene, QGraphicsView* view)
        : scene(scene), view(view) {}
    void drawChessboard();
    void drawPossibleMoves(QList<QPointF> coordinates);
    void deletePossibleMoves();
    QPushButton* addToChessboard(ChessPiece* piece);
};
#endif	// CHESSBOARD_H
