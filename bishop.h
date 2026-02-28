#ifndef BISHOP_H
#define BISHOP_H
#include "chesspiece.h"

class Bishop : ChessPiece {
   public:
    QPointF position;
    Bishop(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// BISHOP_H
