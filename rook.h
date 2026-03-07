#ifndef ROOK_H
#define ROOK_H
#include "chesspiece.h"

class Rook : public ChessPiece {
   public:
    bool isProtected;

    Rook(QPointF position, QString color, bool isProtected)
        : ChessPiece(position, color), isProtected(isProtected) {}

    QList<QPointF> possibleMoves(int cellSize,
                                 QList<QPointF> coordinatesOfAllPieces,
                                 QList<QPointF> coordinatesOfWhitePieces,
                                 QList<QPointF> coordinatesOfBlackPieces,
                                 int counterOfMoves) const override;
};

#endif	// ROOK_H
