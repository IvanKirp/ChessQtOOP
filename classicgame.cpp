#include "classicgame.h"
#include <QDebug>

void ClassicGame::ChessPieceManager(int cellSize) {
    for (int i = 0; i < 8; i++) {
        allChessPieces.append(
            new Pawn(QPointF(i * cellSize, 6 * cellSize), "white", false));
    }
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7)
            allChessPieces.append(
                new Rook(QPointF(i * cellSize, 7 * cellSize), "white", false));
        else if (i == 1 || i == 6)
            allChessPieces.append(new Knight(
                QPointF(i * cellSize, 7 * cellSize), "white", false));
        else if (i == 2 || i == 5)
            allChessPieces.append(new Bishop(
                QPointF(i * cellSize, 7 * cellSize), "white", false));
        else if (i == 3)
            allChessPieces.append(
                new Queen(QPointF(i * cellSize, 7 * cellSize), "white", false));
        else if (i == 4)
            allChessPieces.append(
                new King(QPointF(i * cellSize, 7 * cellSize), "white", false));
    }
    for (int i = 0; i < 8; i++) {
        allChessPieces.append(
            new Pawn(QPointF(i * cellSize, 1 * cellSize), "black", false));
    }
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7)
            allChessPieces.append(
                new Rook(QPointF(i * cellSize, 0), "black", false));
        else if (i == 1 || i == 6)
            allChessPieces.append(
                new Knight(QPointF(i * cellSize, 0), "black", false));
        else if (i == 2 || i == 5)
            allChessPieces.append(
                new Bishop(QPointF(i * cellSize, 0), "black", false));
        else if (i == 3)
            allChessPieces.append(
                new Queen(QPointF(i * cellSize, 0), "black", false));
        else if (i == 4)
            allChessPieces.append(
                new King(QPointF(i * cellSize, 0), "black", false));
    }
    for (int i = 0; i < 32; i++) {
        allChessPieceButtons.append(
            newBoard->addToChessboard(allChessPieces[i]));
    }

    updateCoordinates();
    for (int i = 0; i < allChessPieces.size(); i++) {
        QObject::connect(allChessPieceButtons[i], &QPushButton::clicked,
                         [this, i]() { this->getPossibleMoves(i); });
    }
}
