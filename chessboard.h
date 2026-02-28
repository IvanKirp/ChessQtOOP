#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>
#include <QGraphicsScene>

class ChessBoard {
   public:
    ChessBoard();
    QRectF boundingRect() const;
    void drawChessboard(QGraphicsScene* scene);

   public:
    int cellSize = 100;
};
#endif	// CHESSBOARD_H
