#ifndef KNIGHT_H
#define KNIGHT_H
#include "chesspiece.h"

class Knight : ChessPiece {
   public:
    QPointF position;
    Knight(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// KNIGHT_H
