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

        if (allChessPieces[index]->getName() == "Pawn") {
            QList<int> nearPawns;
            for (int i = 0; i < allChessPieces.size(); i++) {
                if (allChessPieces[i]->getName() == "Pawn" &&
                    std::abs(allChessPieces[index]->position.x() -
                             allChessPieces[i]->position.x()) == cellSize &&
                    allChessPieces[index]->getColor() !=
                        allChessPieces[i]->getColor())
                    nearPawns.append(i);
            }
            qDebug() << "nearPawns" << nearPawns;

            for (int i = nearPawns.size() - 1; i >= 0; i--) {
                if (dynamic_cast<Pawn*>(allChessPieces[nearPawns[i]])
                            ->getPassageState() == true &&
                    allChessPieces[index]->position.y() ==
                        allChessPieces[nearPawns[i]]->position.y()) {
                    QPointF coords =
                        allChessPieces[index]->isWhite()
                            ? QPointF(
                                  allChessPieces[nearPawns[i]]->position.x(),
                                  allChessPieces[nearPawns[i]]->position.y() -
                                      cellSize)
                            : QPointF(
                                  allChessPieces[nearPawns[i]]->position.x(),
                                  allChessPieces[nearPawns[i]]->position.y() +
                                      cellSize);
                    possibleMovesOfThisPiece.append(coords);
                    mouseEventMediator->updateIndexOfTakingOnPassage(
                        nearPawns[i]);
                    qDebug() << "nearPawns[i]" << nearPawns[i];
                    qDebug() << "nearPawns[i]"
                             << mouseEventMediator->getIndexOfTakingOnPassage();
                } else
                    nearPawns.removeAt(i);
            }
            if (nearPawns.isEmpty())
                mouseEventMediator->updateIndexOfTakingOnPassage(-1);
        }

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

        newBoard->drawPossibleMoves(possibleMovesOfThisPiece);
        possibleMovesOfThisPiece.clear();
        indexForRemove.clear();
    }
    qDebug() << "nearPawns[i]"
             << mouseEventMediator->getIndexOfTakingOnPassage();
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

    qDebug() << "1";
    qDebug() << "indexOfTakingOnPassage"
             << mouseEventMediator->getIndexOfTakingOnPassage();

    qDebug() << "до хода";
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getName() == "Pawn") {
            qDebug()
                << i
                << dynamic_cast<Pawn*>(allChessPieces[i])->getPassageState();
        }
    }


    if (allChessPieces[indexOfNowButton]->getName() == "Pawn") {
        if (std::abs(moveTo.y() -
                     allChessPieces[indexOfNowButton]->position.y()) ==
            2 * cellSize) {
            qDebug() << "2";
            dynamic_cast<Pawn*>(allChessPieces[indexOfNowButton])
                ->setPassageState(true);
        } else if (mouseEventMediator->getIndexOfTakingOnPassage() != -1) {
            int indexOfTakingOnPassage =
                mouseEventMediator->getIndexOfTakingOnPassage();
            qDebug() << "3";
            newBoard->deleteFromChessboard(
                allChessPieceButtons[indexOfTakingOnPassage]);
            allChessPieces[indexOfTakingOnPassage]->position = QPointF(-1, -1);
        }
    }

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


    qDebug() << indexOfNowButton;
    clearPawnStates(indexOfNowButton);
    counterOfMoves++;

    qDebug() << "после хода";
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getName() == "Pawn") {
            qDebug()
                << i
                << dynamic_cast<Pawn*>(allChessPieces[i])->getPassageState();
        }
    }
}

void GameMode::taking(int indexOfTakingPiece) {
    newBoard->deletePossibleMoves();

    if (!canBeTakenPieces.contains(coordinatesOfAllPieces[indexOfTakingPiece]))
        return;

    QPointF moveTo = allChessPieces[indexOfTakingPiece]->position;
    int indexOfNowButton = mouseEventMediator->getIndex();

    if (!isCanMove(indexOfNowButton))
        return;

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

    clearPawnStates(indexOfNowButton);
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

        if (!castlingIsPossible(indexOfKing, kingMoveTo)) {
            getPossibleMoves(indexOfRook);
            mouseEventMediator->updateIndex(indexOfRook);
            indexOfLastButton = indexOfRook;
            return;
        }

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

        if (!castlingIsPossible(indexOfKing, kingMoveTo)) {
            getPossibleMoves(indexOfRook);
            mouseEventMediator->updateIndex(indexOfRook);
            indexOfLastButton = indexOfRook;
            return;
        }

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

    clearPawnStates(indexOfKing);
    counterOfMoves++;
}

bool GameMode::castlingIsPossible(int indexOfKing, QPointF kingMoveTo) {
    QPointF king = allChessPieces[indexOfKing]->position;

    int colorIndexOfKing;
    bool isPossible = true;
    if (allChessPieces[indexOfKing]->isWhite()) {
        colorIndexOfKing = coordinatesOfWhitePieces.indexOf(king);
    } else if (allChessPieces[indexOfKing]->isBlack()) {
        colorIndexOfKing = coordinatesOfBlackPieces.indexOf(king);
    }
    if (king.x() <= kingMoveTo.x()) {
        for (int i = king.x(); i <= kingMoveTo.x(); i += cellSize) {
            coordinatesOfAllPieces[indexOfKing] = QPointF(i, king.y());
            if (allChessPieces[indexOfKing]->isWhite()) {
                coordinatesOfWhitePieces[colorIndexOfKing] =
                    QPointF(i, king.y());
                if (isCheckForWhiteKing())
                    isPossible = false;
            } else if (allChessPieces[indexOfKing]->isBlack()) {
                coordinatesOfBlackPieces[colorIndexOfKing] =
                    QPointF(i, king.y());
                if (isCheckForBlackKing())
                    isPossible = false;
            }
        }
        coordinatesOfAllPieces[indexOfKing] = king;
        if (allChessPieces[indexOfKing]->isWhite()) {
            coordinatesOfWhitePieces[colorIndexOfKing] = king;
        } else if (allChessPieces[indexOfKing]->isBlack()) {
            coordinatesOfBlackPieces[colorIndexOfKing] = king;
        }
    } else if (king.x() > kingMoveTo.x()) {
        for (int i = kingMoveTo.x(); i <= king.x(); i += cellSize) {
            coordinatesOfAllPieces[indexOfKing] = QPointF(i, king.y());
            if (allChessPieces[indexOfKing]->isWhite()) {
                coordinatesOfWhitePieces[colorIndexOfKing] =
                    QPointF(i, king.y());
                if (isCheckForWhiteKing())
                    isPossible = false;
            } else if (allChessPieces[indexOfKing]->isBlack()) {
                coordinatesOfBlackPieces[colorIndexOfKing] =
                    QPointF(i, king.y());
                if (isCheckForBlackKing())
                    isPossible = false;
            }
        }
        coordinatesOfAllPieces[indexOfKing] = king;
        if (allChessPieces[indexOfKing]->isWhite()) {
            coordinatesOfWhitePieces[colorIndexOfKing] = king;
        } else if (allChessPieces[indexOfKing]->isBlack()) {
            coordinatesOfBlackPieces[colorIndexOfKing] = king;
        }
    }
    return isPossible;
}

void GameMode::clearPawnStates(int indexOfNowButton) {
    if (allChessPieces[indexOfNowButton]->isWhite()) {
        for (int i = 0; i < allChessPieces.size(); i++) {
            if (allChessPieces[i]->getName() == "Pawn" &&
                allChessPieces[i]->isBlack()) {
                dynamic_cast<Pawn*>(allChessPieces[i])->setPassageState(false);
            }
        }
    } else if (allChessPieces[indexOfNowButton]->isBlack()) {
        for (int i = 0; i < allChessPieces.size(); i++) {
            if (allChessPieces[i]->getName() == "Pawn" &&
                allChessPieces[i]->isWhite()) {
                dynamic_cast<Pawn*>(allChessPieces[i])->setPassageState(false);
            }
        }
    } else
        return;
}

void GameMode::takingOnPassage(int indexOfNowButton, int indexOfTakingOnPassage,
                               QPointF moveTo) {
    /*newBoard->deleteFromChessboard(allChessPieceButtons[indexOfTakingOnPassage]);
    allChessPieces[indexOfTakingOnPassage]->position = QPointF(-1, -1);
    allChessPieceButtons[indexOfNowButton]->move(moveTo.x(), moveTo.y());
    allChessPieces[indexOfNowButton]->position = moveTo;*/
}

//ЕСЛИ ХОД ОБЫЧНЫЙ, ТО ВСЁ ОК, НО ЕСЛИ ВЗЯТИЕ, ТО ПОКА НЕ ОБРАБОТАНА ОТМЕНА ВОЗМОЖНОСТИ ВЗЯТИЯ НА ПРОХОДЕ
