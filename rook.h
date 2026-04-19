#ifndef ROOK_H
#define ROOK_H
#include "chesspiece.h"

class Rook : public ChessPiece {
   public:
    Rook(QPointF position, QString color, bool isCanToCastle)
        : ChessPiece(position, color), isCanToCastle(isCanToCastle) {
        name = "Rook";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;

    bool getCastlingState() const { return isCanToCastle; }
    void setCastlingState(bool state) { isCanToCastle = state; }

   private:
    bool isCanToCastle;
};

#endif	// ROOK_H
