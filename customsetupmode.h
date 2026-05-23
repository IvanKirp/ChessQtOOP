#ifndef CUSTOMSETUPMODE_H
#define CUSTOMSETUPMODE_H

#include <QList>
#include <QPointF>
#include "gamemode.h"

class CustomSetupMode : public GameMode {
   public:
    CustomSetupMode(ChessBoard* newBoard,
                    QList<QPushButton*> choosePieceButtons)
        : GameMode(newBoard), choosePieceButtons(choosePieceButtons) {
        mouseEventMediator->setCustom(this);
        mouseEventMediator->setConnection();
    }

    void ChessPieceManager() override;

    void addPiece();

    QList<ChessPiece*> choosenPieces;
    QList<QPushButton*> choosenPieceButtons;
    QList<QPushButton*> choosePieceButtons;

   protected:
    int lastChoosenPiece = -1;
    bool isDeleting = false;
    bool setCastling = false;
    bool setTakingOnPassage = false;
};

#endif	// CUSTOMSETUPMODE_H
