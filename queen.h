#ifndef QUEEN_H
#define QUEEN_H
#include "chesspiece.h"

class Queen : public ChessPiece {
   public:
    bool isProtected = false;

    Queen(QPointF position, QString color) : ChessPiece(position, color) {
        name = "Queen";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// QUEEN_H
