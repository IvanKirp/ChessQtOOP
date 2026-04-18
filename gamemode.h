#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "bishop.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "king.h"
#include "knight.h"
#include "mouseeventmediator.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

class GameMode : public QObject {
    Q_OBJECT
   public:
    ChessBoard* newBoard;
    int cellSize = newBoard->cellSize;
    int counterOfMoves = 1;
    int indexOfLastButton = -1;
    QList<QPointF> canBeTakenPieces;
    QList<ChessPiece*> allChessPieces;
    QList<QPushButton*> allChessPieceButtons;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();

    GameMode(ChessBoard* newBoard, QList<QPushButton*> allChessPieceButtons)
        : newBoard(newBoard), allChessPieceButtons(allChessPieceButtons) {}

    QList<QPointF> coordinatesOfAllPieces;
    QList<QPointF> coordinatesOfWhitePieces;
    QList<QPointF> coordinatesOfBlackPieces;

    virtual void ChessPieceManager(int cellSize) = 0;
    void updateCoordinates();
    void getPossibleMoves(int index);
    bool isCheckForWhiteKing();
    bool isCheckForBlackKing();
    bool isCanMove(int i);

   public slots:
    void move();
    void taking(int indexOfTakingPiece);
};

#endif	// GAMEMODE_H
