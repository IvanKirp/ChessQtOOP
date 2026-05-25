#ifndef FISCHERCHESS_H
#define FISCHERCHESS_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class FischerChess : public GameMode {
   public:
    FischerChess(ChessBoard* newBoard, int numberOfPosition)
        : GameMode(newBoard), numberOfPosition(numberOfPosition) {
        nameOfMode = "Шахматы Фишера (960)";
    }

    void ChessPieceManager() override;
    QString getStartPosition(int number);

   protected:
    int numberOfPosition;
};

#endif	// FISCHERCHESS_H
