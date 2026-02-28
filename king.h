#ifndef KING_H
#define KING_H
#include "chesspiece.h"

class King : ChessPiece {
   public:
    QPointF position;
    King(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// KING_H
