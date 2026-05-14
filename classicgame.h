#ifndef CLASSICGAME_H
#define CLASSICGAME_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class ClassicGame : public GameMode {
   public:
    ClassicGame(ChessBoard* newBoard) : GameMode(newBoard) {}

    void ChessPieceManager() override;
};

#endif	// CLASSICGAME_H
