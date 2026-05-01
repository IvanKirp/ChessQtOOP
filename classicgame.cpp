#include "classicgame.h"
#include <QDebug>
#include "mouseeventmediator.h"

void ClassicGame::ChessPieceManager(int cellSize) {
    for (int i = 0; i < 8; i++) {
        allChessPieces.append(
            new Pawn(QPointF(i * cellSize, 6 * cellSize), "white", false));
    }
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7)
            allChessPieces.append(
                new Rook(QPointF(i * cellSize, 7 * cellSize), "white", true));
        else if (i == 1 || i == 6)
            allChessPieces.append(
                new Knight(QPointF(i * cellSize, 7 * cellSize), "white"));
        else if (i == 2 || i == 5)
            allChessPieces.append(
                new Bishop(QPointF(i * cellSize, 7 * cellSize), "white"));
        else if (i == 3)
            allChessPieces.append(
                new Queen(QPointF(i * cellSize, 7 * cellSize), "white"));
        else if (i == 4)
            allChessPieces.append(
                new King(QPointF(i * cellSize, 7 * cellSize), "white", true));
    }
    for (int i = 0; i < 8; i++) {
        allChessPieces.append(
            new Pawn(QPointF(i * cellSize, 1 * cellSize), "black", false));
    }
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7)
            allChessPieces.append(
                new Rook(QPointF(i * cellSize, 0), "black", true));
        else if (i == 1 || i == 6)
            allChessPieces.append(
                new Knight(QPointF(i * cellSize, 0), "black"));
        else if (i == 2 || i == 5)
            allChessPieces.append(
                new Bishop(QPointF(i * cellSize, 0), "black"));
        else if (i == 3)
            allChessPieces.append(new Queen(QPointF(i * cellSize, 0), "black"));
        else if (i == 4)
            allChessPieces.append(
                new King(QPointF(i * cellSize, 0), "black", true));
    }
    for (int i = 0; i < 32; i++) {
        allChessPieceButtons.append(
            newBoard->addToChessboard(allChessPieces[i]));
    }

    /*allChessPieces.append(new Bishop(QPointF(300, 500), "white"));
    allChessPieces.append(new Knight(QPointF(500, 200), "black"));
    allChessPieces.append(new Rook(QPointF(400, 400), "white"));
    allChessPieces.append(new Pawn(QPointF(200, 400), "white"));
    allChessPieces.append(new Pawn(QPointF(500, 500), "black"));
    allChessPieces.append(new Queen(QPointF(200, 500), "black"));
    allChessPieces.append(new King(QPointF(400, 500), "white", true));
    allChessPieces.append(new King(QPointF(300, 300), "black", true));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[32]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[33]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[34]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[35]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[36]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[37]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[38]));
    allChessPieceButtons.append(newBoard->addToChessboard(allChessPieces[39]));*/
    updateCoordinates();
    qDebug() << coordinatesOfAllPieces;
    qDebug() << isCheckForWhiteKing();
    qDebug() << isCheckForBlackKing();
    for (int i = 0; i < allChessPieceButtons.size(); i++) {
        connect(allChessPieceButtons[i], &QPushButton::clicked,
                [this, i]() { chessPieceConnection(i); });
    }
}
