#ifndef CLASSICGAME_H
#define CLASSICGAME_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class ClassicGame : public GameMode {
   public:
    ClassicGame(ChessBoard* newBoard, QList<QPushButton*> allChessPieceButtons)
        : GameMode(newBoard, allChessPieceButtons) {}

    void ChessPieceManager(int cellSize) override;
};

#endif	// CLASSICGAME_H
