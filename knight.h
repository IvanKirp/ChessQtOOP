#ifndef KNIGHT_H
#define KNIGHT_H
#include "chesspiece.h"

class Knight : public ChessPiece {
   public:
    bool isProtected;
    Knight(QPointF position, QString color, bool isProtected)
        : ChessPiece(position, color), isProtected(isProtected) {}

    QList<QPointF> possibleMoves(int cellSize,
                                 QList<QPointF> coordinatesOfAllPieces,
                                 QList<QPointF> coordinatesOfWhitePieces,
                                 QList<QPointF> coordinatesOfBlackPieces,
                                 int counterOfMoves) const override;
};

#endif	// KNIGHT_H
