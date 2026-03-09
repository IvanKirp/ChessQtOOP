#ifndef PAWN_H
#define PAWN_H
#include "chesspiece.h"

class Pawn : public ChessPiece {
   public:
    bool isProtected;

    Pawn(QPointF position, QString color, bool isProtected)
        : ChessPiece(position, color), isProtected(isProtected) {}

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// PAWN_H
