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
    QList<ChessPiece*> allChessPieces;
    QList<QPushButton*> allChessPieceButtons;

    GameMode(ChessBoard* newBoard) : newBoard(newBoard) {}

    virtual void ChessPieceManager(int cellSize) = 0;
};

#endif	// GAMEMODE_H
