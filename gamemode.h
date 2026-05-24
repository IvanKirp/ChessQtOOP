#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "bishop.h"
#include "chessboard.h"
#include "chessnotation.h"
#include "chesspiece.h"
#include "chesstranslator.h"
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
    ChessTranslator* translator = new ChessTranslator();
    int cellSize = newBoard->cellSize;
    int counterOfMoves;
    bool isGameOver;
    int indexOfLastButton = 0;
    QList<QPointF> canBeTakenPieces;
    QList<ChessPiece*> allChessPieces;
    QList<QPushButton*> allChessPieceButtons;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();
    void setChessNotation(ChessNotation* _chessNotation) {
        chessNotation = _chessNotation;
    }

    GameMode(ChessBoard* newBoard) : newBoard(newBoard) {
        mouseEventMediator->setGameMode(this);
        mouseEventMediator->setConnection();
        counterOfMoves = 1;
        isGameOver = false;
    }

    QList<QPointF> coordinatesOfAllPieces;
    QList<QPointF> coordinatesOfWhitePieces;
    QList<QPointF> coordinatesOfBlackPieces;

    virtual void ChessPieceManager() = 0;
    virtual void updateCoordinates();
    void clearAllLists();
    virtual QList<QPointF> getPossibleMoves(int index);
    bool isCheckForWhiteKing();
    bool isCheckForBlackKing();
    bool isCanMove(int i);
    void clearPawnStates(int indexOfNowButton);
    bool castlingIsPossible(int indexOfKing, QPointF kingMoveTo);
    void pawnConversion(int indexOfNowButton, QPointF moveTo,
                        bool isTaking = false);
    void taking(int indexOfTakingPiece);

    void universalCastling(int indexOfKing, int indexOfRook);
    void enableCastling(int indexOfKing, int indexOfRook);

    bool isCheckMateForWhite();
    bool isCheckMateForBlack();
    bool isStaleMateForWhite();
    bool isStaleMateForBlack();
    virtual void gameOver();
    void disableAllButtons();
    void enableAllButtons();

    void chessPieceConnection(int i);
    void castlingHandler(int i);
    void whiteMoveHandler(int i);
    void blackMoveHandler(int i);
    void takingHandler(int i);

   protected:
    ChessNotation* chessNotation;
   public slots:
    void move();

   signals:
    void moveIsMade();
    void startGame();
    void home();
};

#endif	// GAMEMODE_H
