#ifndef READONLYMODE_H
#define READONLYMODE_H
#include <QPair>
#include "gamemode.h"

class ReadOnlyMode : public GameMode {
   public:
    ReadOnlyMode(ChessBoard* newBoard) : GameMode(newBoard) {
        mouseEventMediator->setConnection();
    }

    void ChessPieceManager() override;
    void right();
    void left();

   protected:
    QList<QString> allPositions;
    void getAllPositions();
    QPair<int, int> findKingAndRook(QString color, bool isLong = false);
    int positionToIndexInString(QPointF pos);
};

#endif	// READONLYMODE_H
