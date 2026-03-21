#include "gamemode.h"

#include <QDebug>

void GameMode::updateCoordinates() {
    for (int i = 0; i < allChessPieces.size(); i++) {
        coordinatesOfAllPieces.append(allChessPieces[i]->position);
        if (allChessPieces[i]->isWhite())
            coordinatesOfWhitePieces.append(allChessPieces[i]->position);
        else if (allChessPieces[i]->isBlack())
            coordinatesOfBlackPieces.append(allChessPieces[i]->position);
    }
}

void GameMode::getPossibleMoves(int index) {
    QList<QPointF> possibleMovesOfThisPiece =
        allChessPieces[index]->possibleMoves(cellSize, coordinatesOfAllPieces,
                                             coordinatesOfWhitePieces,
                                             coordinatesOfBlackPieces);
    qDebug() << possibleMovesOfThisPiece;
    qDebug() << allChessPieces[index]->getName();
}

void GameMode::updateImpossibleKingsMoves() {
    QList<int> indexesOfKings;
    QList<QPointF> _impossibleMoves;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getName() == "King") {
            indexesOfKings.append(i);
        }
    }

    for (int i = 0; i < indexesOfKings.size(); i++) {
        if (allChessPieces[indexesOfKings[i]]->isWhite()) {

        } else if (allChessPieces[indexesOfKings[i]]->isBlack()) {
        }
    }
}
