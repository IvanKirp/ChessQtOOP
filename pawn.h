#ifndef PAWN_H
#define PAWN_H
#include "chesspiece.h"

class Pawn : ChessPiece {
   public:
    QPointF position;
    Pawn(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// PAWN_H
