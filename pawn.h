#ifndef PAWN_H
#define PAWN_H
#include "chesspiece.h"

class Pawn : public ChessPiece {
   public:
    Pawn(QPointF position, QString color, bool isCanBeTakenOnPassage)
        : ChessPiece(position, color),
          isCanBeTakenOnPassage(isCanBeTakenOnPassage) {
        name = "Pawn";
    }

    QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const override;

    bool getPassageState() const { return isCanBeTakenOnPassage; }
    void setPassageState(bool state) { isCanBeTakenOnPassage = state; }

   private:
    bool isCanBeTakenOnPassage;
};

#endif	// PAWN_H
