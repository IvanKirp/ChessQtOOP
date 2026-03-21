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
    newBoard->deletePossibleMoves();

    QList<QPointF> possibleMovesOfThisPiece =
        allChessPieces[index]->possibleMoves(cellSize, coordinatesOfAllPieces,
                                             coordinatesOfWhitePieces,
                                             coordinatesOfBlackPieces);
    int indexOfColorCoordinates;
    QList<int> indexForRemove;

    for (int i = 0; i < possibleMovesOfThisPiece.size(); i++) {
        coordinatesOfAllPieces[index] = possibleMovesOfThisPiece[i];
        if (allChessPieces[index]->isWhite()) {
            qDebug() << "www";
            indexOfColorCoordinates = coordinatesOfWhitePieces.indexOf(
                allChessPieces[index]->position);
            coordinatesOfWhitePieces[indexOfColorCoordinates] =
                possibleMovesOfThisPiece[i];
            if (!isCheckForWhiteKing()) {
                qDebug() << "www1";
                coordinatesOfAllPieces[index] = allChessPieces[index]->position;
                coordinatesOfWhitePieces[indexOfColorCoordinates] =
                    allChessPieces[index]->position;
            } else if (isCheckForWhiteKing()) {
                qDebug() << "www2";
                coordinatesOfAllPieces[index] = allChessPieces[index]->position;
                coordinatesOfWhitePieces[indexOfColorCoordinates] =
                    allChessPieces[index]->position;
                indexForRemove.append(i);
            }
        }
    }

    for (int i = indexForRemove.size(); i > 0; i--) {
        possibleMovesOfThisPiece.removeAt(indexForRemove[i]);
    }

    newBoard->drawPossibleMoves(possibleMovesOfThisPiece);
    possibleMovesOfThisPiece.clear();
}

bool GameMode::isCheckForWhiteKing() {
    int indexOfKing;
    QList<QPointF> impossibleWhiteKingMoves;
    QList<QPointF> tempList;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getName() == "King" &&
            allChessPieces[i]->isWhite()) {
            indexOfKing = i;
        }
    }

    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->isBlack()) {
            tempList.append(allChessPieces[i]->possibleMoves(
                cellSize, coordinatesOfAllPieces, coordinatesOfWhitePieces,
                coordinatesOfBlackPieces));
            for (int j = 0; j < tempList.size(); j++) {
                if (!impossibleWhiteKingMoves.contains(tempList[j]))
                    impossibleWhiteKingMoves.append(tempList[j]);
            }
            tempList.clear();
        }
    }
    int kingIndex =
        coordinatesOfAllPieces.indexOf(allChessPieces[indexOfKing]->position);
    if (impossibleWhiteKingMoves.contains(coordinatesOfAllPieces[kingIndex])) {
        impossibleWhiteKingMoves.clear();
        return true;
    } else {
        impossibleWhiteKingMoves.clear();
        return false;
    }
}

bool GameMode::isCheckForBlackKing() {
    int indexOfKing;
    QList<QPointF> impossibleBlackKingMoves;
    QList<QPointF> tempList;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getName() == "King" &&
            allChessPieces[i]->isBlack()) {
            indexOfKing = i;
        }
    }

    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->isWhite()) {
            tempList.append(allChessPieces[i]->possibleMoves(
                cellSize, coordinatesOfAllPieces, coordinatesOfWhitePieces,
                coordinatesOfBlackPieces));
            for (int j = 0; j < tempList.size(); j++) {
                if (!impossibleBlackKingMoves.contains(tempList[j]))
                    impossibleBlackKingMoves.append(tempList[j]);
            }
            tempList.clear();
        }
    }

    if (impossibleBlackKingMoves.contains(
            allChessPieces[indexOfKing]->position)) {
        impossibleBlackKingMoves.clear();
        return true;
    } else {
        impossibleBlackKingMoves.clear();
        return false;
    }
}
