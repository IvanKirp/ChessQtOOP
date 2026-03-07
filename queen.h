#ifndef QUEEN_H
#define QUEEN_H
#include "chesspiece.h"

class Queen : public ChessPiece {
   public:
    bool isProtected;

    Queen(QPointF position, QString color, bool isProtected)
        : ChessPiece(position, color), isProtected(isProtected) {}

    QList<QPointF> possibleMoves(int cellSize,
                                 QList<QPointF> coordinatesOfAllPieces,
                                 QList<QPointF> coordinatesOfWhitePieces,
                                 QList<QPointF> coordinatesOfBlackPieces,
                                 int counterOfMoves) const override;
};

#endif	// QUEEN_H
