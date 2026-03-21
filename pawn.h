#ifndef PAWN_H
#define PAWN_H
#include "chesspiece.h"

class Pawn : public ChessPiece {
   public:
    bool isProtected = false;
    bool isCanBeTakenOnPassage = false;

    Pawn(QPointF position, QString color) : ChessPiece(position, color) {
        name = "Pawn";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;
};

#endif	// PAWN_H
