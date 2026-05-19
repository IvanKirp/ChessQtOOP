#ifndef ANTICHESS_H
#define ANTICHESS_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class AntiChess : public GameMode {
   public:
    AntiChess(ChessBoard* newBoard) : GameMode(newBoard) {}

    void ChessPieceManager() override;

   protected:
    QList<QPointF> getPossibleMoves(int index) override;
    void checkForTaking();
    bool isMustBeTaking = false;
};

#endif	// ANTICHESS_H
