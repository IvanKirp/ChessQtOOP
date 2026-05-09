#ifndef FISCHERCHESS_H
#define FISCHERCHESS_H

#include "gamemode.h"

#include <QList>
#include <QPointF>

class FischerChess : public GameMode {
   public:
    FischerChess(ChessBoard* newBoard, QList<QPushButton*> allChessPieceButtons,
                 int numberOfPosition)
        : GameMode(newBoard, allChessPieceButtons),
          numberOfPosition(numberOfPosition) {}

    void ChessPieceManager() override;
    QString getStartPosition(int number);

   protected:
    int numberOfPosition;
};

#endif	// FISCHERCHESS_H
