#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "bishop.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

class GameMode {
   public:
    ChessBoard* newBoard;
    int cellSize = newBoard->cellSize;
    QList<ChessPiece*> allChessPieces;
    QList<QPushButton*> allChessPieceButtons;

    GameMode(ChessBoard* newBoard, QList<QPushButton*> allChessPieceButtons)
        : newBoard(newBoard), allChessPieceButtons(allChessPieceButtons) {}

    QList<QPointF> coordinatesOfAllPieces;
    QList<QPointF> coordinatesOfWhitePieces;
    QList<QPointF> coordinatesOfBlackPieces;

    virtual void ChessPieceManager(int cellSize) = 0;
    void updateCoordinates();
    void getPossibleMoves(int index);
};

#endif	// GAMEMODE_H
