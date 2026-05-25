#ifndef READONLYMODE_H
#define READONLYMODE_H
#include "gamemode.h"

class ReadOnlyMode : public GameMode {
   public:
    ReadOnlyMode(ChessBoard* newBoard) : GameMode(newBoard) {}

    void ChessPieceManager() override;
};

#endif	// READONLYMODE_H
