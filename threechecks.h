#ifndef THREECHECKS_H
#define THREECHECKS_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class ThreeChecks : public GameMode {
   public:
    ThreeChecks(ChessBoard* newBoard) : GameMode(newBoard) {}

    void ChessPieceManager() override;

   private:
    void updateCoordinates() override;
    void gameOver() override;
    void updateCountersOfCheck();
    int counterOfChecksToWhite = 0;
    int counterOfChecksToBlack = 0;
};

#endif	// THREECHECKS_H
