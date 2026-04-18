#include "gamemode.h"

#include <QDebug>

void GameMode::updateCoordinates() {
    coordinatesOfAllPieces.clear();
    coordinatesOfWhitePieces.clear();
    coordinatesOfBlackPieces.clear();
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
    canBeTakenPieces.clear();

    if (isCanMove(index)) {
        QList<QPointF> possibleMovesOfThisPiece =
            allChessPieces[index]->possibleMoves(
                cellSize, coordinatesOfAllPieces, coordinatesOfWhitePieces,
                coordinatesOfBlackPieces);
        int indexOfColorCoordinates;
        int canBeTakenPieceIndex;
        int canBeTakenPieceColorIndex;
        QPointF canBeTakenPiecePosition;
        QList<int> indexForRemove;

        for (int i = 0; i < possibleMovesOfThisPiece.size(); i++) {
            if (allChessPieces[index]->isWhite()) {

                if (coordinatesOfBlackPieces.contains(
                        possibleMovesOfThisPiece[i]) &&
                    coordinatesOfAllPieces.contains(
                        possibleMovesOfThisPiece[i])) {
                    canBeTakenPieceColorIndex =
                        coordinatesOfBlackPieces.indexOf(
                            possibleMovesOfThisPiece[i]);
                    canBeTakenPieceIndex = coordinatesOfAllPieces.indexOf(
                        possibleMovesOfThisPiece[i]);
                    canBeTakenPiecePosition =
                        allChessPieces[canBeTakenPieceIndex]->position;
                    coordinatesOfBlackPieces[canBeTakenPieceColorIndex] =
                        QPointF(-1, -1);
                    allChessPieces[canBeTakenPieceIndex]->position =
                        QPointF(-1, -1);
                }

                coordinatesOfAllPieces[index] = possibleMovesOfThisPiece[i];
                indexOfColorCoordinates = coordinatesOfWhitePieces.indexOf(
                    allChessPieces[index]->position);
                coordinatesOfWhitePieces[indexOfColorCoordinates] =
                    possibleMovesOfThisPiece[i];

                if (!isCheckForWhiteKing()) {
                    coordinatesOfAllPieces[index] =
                        allChessPieces[index]->position;
                    coordinatesOfWhitePieces[indexOfColorCoordinates] =
                        allChessPieces[index]->position;
                    if (canBeTakenPieceColorIndex >= 0 &&
                        canBeTakenPieceIndex >= 0) {
                        coordinatesOfBlackPieces[canBeTakenPieceColorIndex] =
                            canBeTakenPiecePosition;
                        allChessPieces[canBeTakenPieceIndex]->position =
                            canBeTakenPiecePosition;
                    }

                } else if (isCheckForWhiteKing()) {
                    coordinatesOfAllPieces[index] =
                        allChessPieces[index]->position;
                    coordinatesOfWhitePieces[indexOfColorCoordinates] =
                        allChessPieces[index]->position;
                    if (canBeTakenPieceColorIndex >= 0 &&
                        canBeTakenPieceIndex >= 0) {
                        coordinatesOfBlackPieces[canBeTakenPieceColorIndex] =
                            canBeTakenPiecePosition;
                        allChessPieces[canBeTakenPieceIndex]->position =
                            canBeTakenPiecePosition;
                    }
                    indexForRemove.append(i);
                }

            } else if (allChessPieces[index]->isBlack()) {

                if (coordinatesOfWhitePieces.contains(
                        possibleMovesOfThisPiece[i]) &&
                    coordinatesOfAllPieces.contains(
                        possibleMovesOfThisPiece[i])) {
                    canBeTakenPieceColorIndex =
                        coordinatesOfWhitePieces.indexOf(
                            possibleMovesOfThisPiece[i]);
                    canBeTakenPieceIndex = coordinatesOfAllPieces.indexOf(
                        possibleMovesOfThisPiece[i]);
                    canBeTakenPiecePosition =
                        allChessPieces[canBeTakenPieceIndex]->position;
                    coordinatesOfWhitePieces[canBeTakenPieceColorIndex] =
                        QPointF(-1, -1);
                    allChessPieces[canBeTakenPieceIndex]->position =
                        QPointF(-1, -1);
                }

                coordinatesOfAllPieces[index] = possibleMovesOfThisPiece[i];
                indexOfColorCoordinates = coordinatesOfBlackPieces.indexOf(
                    allChessPieces[index]->position);
                coordinatesOfBlackPieces[indexOfColorCoordinates] =
                    possibleMovesOfThisPiece[i];

                if (!isCheckForBlackKing()) {
                    coordinatesOfAllPieces[index] =
                        allChessPieces[index]->position;
                    coordinatesOfBlackPieces[indexOfColorCoordinates] =
                        allChessPieces[index]->position;
                    if (canBeTakenPieceColorIndex >= 0 &&
                        canBeTakenPieceIndex >= 0) {
                        coordinatesOfWhitePieces[canBeTakenPieceColorIndex] =
                            canBeTakenPiecePosition;
                        allChessPieces[canBeTakenPieceIndex]->position =
                            canBeTakenPiecePosition;
                    }

                } else if (isCheckForBlackKing()) {
                    coordinatesOfAllPieces[index] =
                        allChessPieces[index]->position;
                    coordinatesOfBlackPieces[indexOfColorCoordinates] =
                        allChessPieces[index]->position;
                    if (canBeTakenPieceColorIndex >= 0 &&
                        canBeTakenPieceIndex >= 0) {
                        coordinatesOfWhitePieces[canBeTakenPieceColorIndex] =
                            canBeTakenPiecePosition;
                        allChessPieces[canBeTakenPieceIndex]->position =
                            canBeTakenPiecePosition;
                    }
                    indexForRemove.append(i);
                }
            }
        }


        for (int i = indexForRemove.size() - 1; i >= 0; i--) {
            possibleMovesOfThisPiece.removeAt(indexForRemove[i]);
        }

        for (int i = 0; i < possibleMovesOfThisPiece.size(); i++) {
            if (allChessPieces[index]->isWhite() &&
                coordinatesOfBlackPieces.contains(possibleMovesOfThisPiece[i]))
                canBeTakenPieces.append(possibleMovesOfThisPiece[i]);
            else if (allChessPieces[index]->isBlack() &&
                     coordinatesOfWhitePieces.contains(
                         possibleMovesOfThisPiece[i]))
                canBeTakenPieces.append(possibleMovesOfThisPiece[i]);
        }
        qDebug() << canBeTakenPieces;
        newBoard->drawPossibleMoves(possibleMovesOfThisPiece);
        qDebug() << possibleMovesOfThisPiece;
        possibleMovesOfThisPiece.clear();
        indexForRemove.clear();
    }
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
    if (impossibleWhiteKingMoves.contains(
            coordinatesOfAllPieces[indexOfKing])) {
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
            coordinatesOfAllPieces[indexOfKing])) {
        impossibleBlackKingMoves.clear();
        return true;
    } else {
        impossibleBlackKingMoves.clear();
        return false;
    }
}

bool GameMode::isCanMove(int i) {
    if (counterOfMoves % 2 == 1 && allChessPieces[i]->isWhite())
        return true;
    else if (counterOfMoves % 2 == 0 && allChessPieces[i]->isBlack())
        return true;
    else
        return false;
}

void GameMode::move() {
    newBoard->deletePossibleMoves();
    QPointF moveTo = mouseEventMediator->getCell();
    int indexOfNowButton = mouseEventMediator->getIndex();
    if (!coordinatesOfAllPieces.contains(moveTo)) {
        int x = moveTo.x();
        int y = moveTo.y();
        allChessPieceButtons[indexOfNowButton]->move(x, y);
        allChessPieces[indexOfNowButton]->position = moveTo;
        updateCoordinates();
    }

    indexOfLastButton = -1;
    counterOfMoves++;
}

void GameMode::taking(int indexOfTakingPiece) {
    newBoard->deletePossibleMoves();
    if (!canBeTakenPieces.contains(coordinatesOfAllPieces[indexOfTakingPiece]))
        return;

    QPointF moveTo = allChessPieces[indexOfTakingPiece]->position;
    int indexOfNowButton = mouseEventMediator->getIndex();
    newBoard->deleteFromChessboard(allChessPieceButtons[indexOfTakingPiece]);
    allChessPieces[indexOfTakingPiece]->position = QPointF(-1, -1);
    int x = moveTo.x();
    int y = moveTo.y();
    allChessPieceButtons[indexOfNowButton]->move(x, y);
    allChessPieces[indexOfNowButton]->position = moveTo;
    updateCoordinates();

    indexOfLastButton = -1;
    counterOfMoves++;
}
