#ifndef ANTICHESS_H
#define ANTICHESS_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class AntiChess : public GameMode {
   public:
    AntiChess(ChessBoard* newBoard) : GameMode(newBoard) {
        nameOfMode = "Поддавки";
    }

    void ChessPieceManager() override;

   protected:
    QList<QPointF> getPossibleMoves(int index) override;
    void gameOver() override;
    void checkForTaking();
    bool isMustBeTaking = false;

   private:
    bool whiteWin();
    bool blackWin();
};

#endif	// ANTICHESS_H
