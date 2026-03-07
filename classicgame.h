#ifndef CLASSICGAME_H
#define CLASSICGAME_H

#include "gamemode.h"

#include <QList>

class ClassicGame : public GameMode {
   public:
    ClassicGame(ChessBoard* newBoard) : GameMode(newBoard) {}

    void ChessPieceManager(int cellSize) override;
};

#endif	// CLASSICGAME_H
