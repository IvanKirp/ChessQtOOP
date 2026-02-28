#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QPointF>
class ChessPiece {
   public:
    ChessPiece();

    virtual QList<QPointF> possibleMoves() const = 0;
};

#endif	// CHESSPIECE_H
