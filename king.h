#ifndef KING_H
#define KING_H
#include "chesspiece.h"

class King : public ChessPiece {
   public:
    King(QPointF position, QString color, bool isCanToCastle)
        : ChessPiece(position, color), isCanToCastle(isCanToCastle) {
        name = "King";
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

#endif	// KING_H
