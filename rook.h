#ifndef ROOK_H
#define ROOK_H
#include "chesspiece.h"

class Rook : public ChessPiece {
   public:
    bool isProtected = false;

    Rook(QPointF position, QString color) : ChessPiece(position, color) {
        name = "Rook";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// ROOK_H
