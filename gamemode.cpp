#include "gamemode.h"

#include <QDebug>

void GameMode::updateCoordinates() {
    for (int i = 0; i < allChessPieces.size(); i++) {
        coordinatesOfAllPieces.append(allChessPieces[i]->position);
        if (allChessPieces[i]->color == "white")
            coordinatesOfWhitePieces.append(allChessPieces[i]->position);
        else if (allChessPieces[i]->color == "black")
            coordinatesOfBlackPieces.append(allChessPieces[i]->position);
    }
}

void GameMode::getPossibleMoves(int index) {
    QList<QPointF> possibleMovesOfThisPiece =
        allChessPieces[index]->possibleMoves(cellSize, coordinatesOfAllPieces,
                                             coordinatesOfWhitePieces,
                                             coordinatesOfBlackPieces);
    qDebug() << possibleMovesOfThisPiece;
}
