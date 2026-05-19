#include "gamemode.h"

#include <QDebug>
#include <QMessageBox>
void GameMode::chessPieceConnection(int i) {
    castlingHandler(i);
    return;
}
void GameMode::castlingHandler(int i) {
    if (allChessPieces[indexOfLastButton]->getName() == "King" &&
        allChessPieces[i]->getName() == "Rook" &&
        allChessPieces[indexOfLastButton]->getColor() ==
            allChessPieces[i]->getColor()) {
        universalCastling(indexOfLastButton, i);
        indexOfLastButton = i;
        return;
    } else {
        whiteMoveHandler(i);
        return;
    }
}
void GameMode::whiteMoveHandler(int i) {
    if (counterOfMoves % 2 == 1 && allChessPieces[i]->getColor() == "white") {
        newBoard->deletePossibleMoves();
        newBoard->drawPossibleMoves(getPossibleMoves(i));
        mouseEventMediator->updateIndex(i);
        indexOfLastButton = i;
        return;
    } else {
        blackMoveHandler(i);
        return;
    }
}
void GameMode::blackMoveHandler(int i) {
    if (counterOfMoves % 2 == 0 && allChessPieces[i]->getColor() == "black") {
        newBoard->deletePossibleMoves();
        newBoard->drawPossibleMoves(getPossibleMoves(i));
        mouseEventMediator->updateIndex(i);
        indexOfLastButton = i;
        return;
    } else {
        takingHandler(i);
        return;
    }
}
void GameMode::takingHandler(int i) {
    taking(i);
    mouseEventMediator->updateIndex(indexOfLastButton);
    return;
}

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

void GameMode::clearAllLists() {
    coordinatesOfAllPieces.clear();
    coordinatesOfWhitePieces.clear();
    coordinatesOfBlackPieces.clear();
    allChessPieces.clear();
    allChessPieceButtons.clear();
}

QList<QPointF> GameMode::getPossibleMoves(int index) {
    canBeTakenPieces.clear();
    newBoard->deletePossibleMoves();

    qDebug() << "counterOfMoves" << counterOfMoves;
    qDebug() << "allPositions";
    for (int i = 0; i < allChessPieces.size(); i++) {
        qDebug() << i << allChessPieces[i]->getName()
                 << allChessPieces[i]->position;
    }
    QList<QPointF> possibleMovesOfThisPiece;
    if (isCanMove(index)) {
        possibleMovesOfThisPiece = allChessPieces[index]->possibleMoves(
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
                    canBeTakenPieces.append(coords);
                } else
                    nearPawns.removeAt(i);
            }
            //if (nearPawns.isEmpty())
            //  mouseEventMediator->updateIndexOfTakingOnPassage(-1);
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
    }
    qDebug() << "this possibleMovesOfThisPiece" << possibleMovesOfThisPiece;
    return possibleMovesOfThisPiece;
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
    QPointF moveTo = mouseEventMediator->getCell();
    int indexOfNowButton = mouseEventMediator->getIndex();

    if (allChessPieces[indexOfNowButton]->getName() == "Pawn") {
        if ((allChessPieces[indexOfNowButton]->isWhite() && moveTo.y() == 0) ||
            (allChessPieces[indexOfNowButton]->isBlack() &&
             moveTo.y() == 7 * cellSize)) {
            pawnConvertion(indexOfNowButton, moveTo);
        } else if (std::abs(moveTo.y() -
                            allChessPieces[indexOfNowButton]->position.y()) ==
                   2 * cellSize) {
            dynamic_cast<Pawn*>(allChessPieces[indexOfNowButton])
                ->setPassageState(true);
        } else if (mouseEventMediator->getIndexOfTakingOnPassage() != -1 &&
                   allChessPieces[mouseEventMediator
                                      ->getIndexOfTakingOnPassage()]
                           ->position.x() == moveTo.x()) {
            int indexOfTakingOnPassage =
                mouseEventMediator->getIndexOfTakingOnPassage();
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


    clearPawnStates(indexOfNowButton);
    counterOfMoves++;
    gameOver();
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

    if (allChessPieces[indexOfNowButton]->getName() == "Pawn") {
        if ((allChessPieces[indexOfNowButton]->isWhite() && moveTo.y() == 0) ||
            (allChessPieces[indexOfNowButton]->isBlack() &&
             moveTo.y() == 7 * cellSize)) {
            pawnConvertion(indexOfNowButton, moveTo);
        }
    }

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
    gameOver();
}

void GameMode::universalCastling(int indexOfKing, int indexOfRook) {
    newBoard->deletePossibleMoves();
    if (dynamic_cast<King*>(allChessPieces[indexOfKing])->getCastlingState() ==
            false ||
        dynamic_cast<Rook*>(allChessPieces[indexOfRook])->getCastlingState() ==
            false) {
        newBoard->deletePossibleMoves();
        newBoard->drawPossibleMoves(getPossibleMoves(indexOfRook));
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
            newBoard->deletePossibleMoves();
            newBoard->drawPossibleMoves(getPossibleMoves(indexOfRook));
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
            newBoard->deletePossibleMoves();
            newBoard->drawPossibleMoves(getPossibleMoves(indexOfRook));
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
            coordinatesOfAllPieces.indexOf(needToBeEmptyCoordinates[i]) !=
                indexOfKing &&
            coordinatesOfAllPieces.indexOf(needToBeEmptyCoordinates[i]) !=
                indexOfRook) {
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
    gameOver();
}

void GameMode::enableCastling(int indexOfKing, int indexOfRook) {
    if (!dynamic_cast<King*>(allChessPieces[indexOfKing]) ||
        !dynamic_cast<Rook*>(allChessPieces[indexOfRook]))
        return;
    King* king = dynamic_cast<King*>(allChessPieces[indexOfKing]);
    Rook* rook = dynamic_cast<Rook*>(allChessPieces[indexOfRook]);
    if (king->isWhite() && rook->isWhite() &&
        king->position.y() == 7 * cellSize &&
        rook->position.y() == 7 * cellSize) {
        king->setCastlingState(true);
        rook->setCastlingState(true);
    } else if (king->isBlack() && rook->isBlack() && king->position.y() == 0 &&
               rook->position.y() == 0) {
        king->setCastlingState(true);
        rook->setCastlingState(true);
    } else
        return;
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

void GameMode::pawnConvertion(int indexOfPawn, QPointF moveTo) {
    QString color;

    if (allChessPieces[indexOfPawn]->isWhite()) {
        color = "white";
        newBoard->addWhitePawnChooseButtons(moveTo);
    } else if (allChessPieces[indexOfPawn]->isBlack()) {
        color = "black";
        newBoard->addBlackPawnChooseButtons(moveTo);
    }

    for (int i = 0; i < 4; i++) {
        QAbstractButton::connect(
            newBoard->pawnChooseButtons[i], &QPushButton::clicked,
            [this, i, moveTo, indexOfPawn, color]() {
                ChessPiece* choosenPiece;
                if (i == 0) {
                    choosenPiece = new Queen(moveTo, color);
                } else if (i == 1) {
                    choosenPiece = new Rook(moveTo, color, false);
                } else if (i == 2) {
                    choosenPiece = new Knight(moveTo, color);
                } else if (i == 3) {
                    choosenPiece = new Bishop(moveTo, color);
                }
                allChessPieces[indexOfPawn] = choosenPiece;
                newBoard->deleteFromChessboard(
                    allChessPieceButtons[indexOfPawn]);
                QPushButton* choosenPieceButton =
                    newBoard->addToChessboard(choosenPiece);
                allChessPieceButtons[indexOfPawn] = choosenPieceButton;
                connect(allChessPieceButtons[indexOfPawn],
                        &QPushButton::clicked, [this, indexOfPawn]() {
                            chessPieceConnection(indexOfPawn);
                        });
                ;
                newBoard->deletePawnChooseButtons();
            });
    }
}

bool GameMode::isCheckMateForWhite() {
    if (!isCheckForWhiteKing())
        return false;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->isWhite() && !getPossibleMoves(i).isEmpty())
            return false;
    }
    return true;
}
bool GameMode::isCheckMateForBlack() {
    if (!isCheckForBlackKing())
        return false;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->isBlack() && !getPossibleMoves(i).isEmpty())
            return false;
    }
    return true;
}
bool GameMode::isStaleMateForWhite() {
    if (isCheckForWhiteKing())
        return false;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->position != QPointF(-1, -1) &&
            allChessPieces[i]->isWhite() &&
            !GameMode::getPossibleMoves(i).isEmpty())
            return false;
    }
    return true;
}
bool GameMode::isStaleMateForBlack() {
    if (isCheckForBlackKing())
        return false;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->position != QPointF(-1, -1) &&
            allChessPieces[i]->isBlack() &&
            !GameMode::getPossibleMoves(i).isEmpty())
            return false;
    }
    return true;
}

void GameMode::gameOver() {
    if (counterOfMoves % 2 == 1) {
        if (isCheckMateForWhite()) {
            QMessageBox::information(newBoard->view, "Победа чёрных!",
                                     "Белым объявлен мат!");
        } else if (isStaleMateForWhite()) {
            QMessageBox::information(newBoard->view, "Ничья!",
                                     "Белым поставили пат!");
        }
    } else if (counterOfMoves % 2 == 0) {
        if (isCheckMateForBlack()) {
            QMessageBox::information(newBoard->view, "Победа белых!",
                                     "Чёрным объявлен мат!");
        } else if (isStaleMateForBlack()) {
            QMessageBox::information(newBoard->view, "Ничья!",
                                     "Чёрным поставили пат!");
        }
    }
}
