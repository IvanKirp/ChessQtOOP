#ifndef ROOK_H
#define ROOK_H
#include "chesspiece.h"

class Rook : ChessPiece {
   public:
    QPointF position;
    Rook(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// ROOK_H
