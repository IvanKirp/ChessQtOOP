#ifndef QEUEN_H
#define QEUEN_H
#include "chesspiece.h"

class Qeuen : ChessPiece {
   public:
    QPointF position;
    Qeuen(QPointF coordinates) : position(coordinates) {}

    QList<QPointF> possibleMoves() const override;
};

#endif	// QEUEN_H
