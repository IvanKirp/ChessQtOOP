#ifndef BISHOP_H
#define BISHOP_H
#include <QString>
#include "chesspiece.h"

class Bishop : public ChessPiece {
   public:
    bool isProtected;

    Bishop(QPointF position, QString color, bool isProtected)
        : ChessPiece(position, color), isProtected(isProtected) {}

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// BISHOP_H
