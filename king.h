#ifndef KING_H
#define KING_H
#include "chesspiece.h"

class King : public ChessPiece {
   public:
    bool isProtected = false;
    King(QPointF position, QString color) : ChessPiece(position, color) {
        name = "King";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// KING_H
