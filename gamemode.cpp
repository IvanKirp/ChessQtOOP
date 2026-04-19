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
        int indexOfColorCoordinates = -1;
        int canBeTakenPieceIndex = -1;
        int canBeTakenPieceColorIndex = -1;
        QPointF canBeTakenPiecePosition = QPointF(-1, -1);
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

    if (allChessPieces[indexOfNowButton]->getName() == "Rook")
        dynamic_cast<Rook*>(allChessPieces[indexOfNowButton])
            ->setCastlingState(false);
    else if (allChessPieces[indexOfNowButton]->getName() == "King")
        dynamic_cast<King*>(allChessPieces[indexOfNowButton])
            ->setCastlingState(false);

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


    if (allChessPieces[indexOfNowButton]->getName() == "Rook")
        dynamic_cast<Rook*>(allChessPieces[indexOfNowButton])
            ->setCastlingState(false);
    else if (allChessPieces[indexOfNowButton]->getName() == "King")
        dynamic_cast<King*>(allChessPieces[indexOfNowButton])
            ->setCastlingState(false);

    counterOfMoves++;
}

void GameMode::universalCastling(int indexOfKing, int indexOfRook) {
    newBoard->deletePossibleMoves();
    if (dynamic_cast<King*>(allChessPieces[indexOfKing])->getCastlingState() ==
            false ||
        dynamic_cast<Rook*>(allChessPieces[indexOfRook])->getCastlingState() ==
            false) {
        getPossibleMoves(indexOfRook);
        mouseEventMediator->updateIndex(indexOfRook);
        indexOfLastButton = indexOfRook;
        return;
    }

    QPointF king = allChessPieces[indexOfKing]->position;
    QPointF rook = allChessPieces[indexOfRook]->position;
    QList<QPointF> needToBeEmptyCoordinates;
    QPointF kingMoveTo;
    QPointF rookMoveTo;

    //короткая рокировка
    if (rook.x() - king.x() > 0) {
        kingMoveTo = QPointF(6 * cellSize, king.y());
        rookMoveTo = QPointF(5 * cellSize, king.y());
        needToBeEmptyCoordinates.append(kingMoveTo);
        needToBeEmptyCoordinates.append(rookMoveTo);
        for (int i = king.x() + cellSize; i < kingMoveTo.x(); i += cellSize) {
            QPointF cell = QPointF(i, king.y());
            if (!needToBeEmptyCoordinates.contains(cell))
                needToBeEmptyCoordinates.append(cell);
        }
    }

    //длинная рокировка
    else if (rook.x() - king.x() < 0) {
        kingMoveTo = QPointF(2 * cellSize, king.y());
        rookMoveTo = QPointF(3 * cellSize, king.y());
        needToBeEmptyCoordinates.append(kingMoveTo);
        needToBeEmptyCoordinates.append(rookMoveTo);
        if (rook.x() == 0) {
            for (int i = rook.x() + cellSize; i < king.x(); i += cellSize) {
                QPointF cell = QPointF(i, king.y());
                if (!needToBeEmptyCoordinates.contains(cell))
                    needToBeEmptyCoordinates.append(cell);
            }
        } else if (rook.x() != 0) {
            for (int i = kingMoveTo.x() + cellSize; i < king.x();
                 i += cellSize) {
                QPointF cell = QPointF(i, king.y());
                if (!needToBeEmptyCoordinates.contains(cell))
                    needToBeEmptyCoordinates.append(cell);
            }
        }
    }

    for (int i = 0; i < needToBeEmptyCoordinates.size(); i++) {
        if (coordinatesOfAllPieces.contains(needToBeEmptyCoordinates[i]) &&
            i != indexOfKing && i != indexOfRook) {
            return;
        }
    }

    allChessPieceButtons[indexOfKing]->move(kingMoveTo.x(), kingMoveTo.y());
    allChessPieceButtons[indexOfRook]->move(rookMoveTo.x(), rookMoveTo.y());
    allChessPieces[indexOfKing]->position = kingMoveTo;
    allChessPieces[indexOfRook]->position = rookMoveTo;
    dynamic_cast<King*>(allChessPieces[indexOfKing])->setCastlingState(false);
    dynamic_cast<Rook*>(allChessPieces[indexOfRook])->setCastlingState(false);
    updateCoordinates();
    counterOfMoves++;
}
