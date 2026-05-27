#include "readonlymode.h"
#include <QDebug>

void ReadOnlyMode::ChessPieceManager() {
    dataStorage->load();
    getDataFromLoad();
    allChessPieces = translator->decryption(startPosition);
    for (int i = 0; i < allChessPieces.size(); i++) {
        allChessPieceButtons.append(
            newBoard->addToChessboard(allChessPieces[i]));
    }

    for (int i = 0; i < moves.size(); i++) {
        chessNotation->writeString(moves[i]);
    }

    mouseEventMediator->setNameOfMode(nameOfMode);
    mouseEventMediator->setResult(result);
    getAllPositions();
    startReadOnlyMode();
}

void ReadOnlyMode::right() {
    if (allPositions.size() == 1)
        return;

    chessNotation->right();

    if (chessNotation->currentMove >= 0 &&
        chessNotation->currentMove < allPositions.size()) {

        for (int i = 0; i < allChessPieceButtons.size(); i++) {
            newBoard->deleteFromChessboard(allChessPieceButtons[i]);
        }
        allChessPieceButtons.clear();

        allChessPieces = translator->decryption(
            allPositions[chessNotation->currentMove + 1]);

        for (int i = 0; i < allChessPieces.size(); i++) {
            allChessPieceButtons.append(
                newBoard->addToChessboard(allChessPieces[i]));
        }
    }
}

void ReadOnlyMode::left() {
    int oldMove = chessNotation->currentMove;
    chessNotation->left();

    if (chessNotation->currentMove >= 0 &&
        chessNotation->currentMove < allPositions.size() &&
        chessNotation->currentMove != oldMove) {

        for (int i = 0; i < allChessPieceButtons.size(); i++) {
            newBoard->deleteFromChessboard(allChessPieceButtons[i]);
        }
        allChessPieceButtons.clear();

        allChessPieces = translator->decryption(
            allPositions[chessNotation->currentMove + 1]);

        for (int i = 0; i < allChessPieces.size(); i++) {
            allChessPieceButtons.append(
                newBoard->addToChessboard(allChessPieces[i]));
        }
    } else if (chessNotation->currentMove == -1) {
        allChessPieces.clear();
        for (int i = 0; i < allChessPieceButtons.size(); i++) {
            newBoard->deleteFromChessboard(allChessPieceButtons[i]);
        }
        allChessPieceButtons.clear();
        allChessPieces = translator->decryption(startPosition);
        for (int i = 0; i < allChessPieces.size(); i++) {
            allChessPieceButtons.append(
                newBoard->addToChessboard(allChessPieces[i]));
        }
    }
}

void ReadOnlyMode::getAllPositions() {
    allPositions.append(startPosition);
    QString pieces = "RNBQK";
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == "---------") {
            allPositions.append(startPosition);
        } else if (moves[i] == "0-0") {
            if ((i + 1) % 2 == 1) {
                QPair<int, int> castling = findKingAndRook("white");
                int K = positionToIndexInString(
                    allChessPieces[castling.first]->position);
                int R = positionToIndexInString(
                    allChessPieces[castling.second]->position);
                QString newPosition =
                    translator->stringMove(allPositions.last(), K, 6);
                newPosition = translator->stringMove(newPosition, R, 5);
                allPositions.append(newPosition);
                allChessPieces = translator->decryption(newPosition);
            } else if ((i + 1) % 2 == 0) {
                QPair<int, int> castling = findKingAndRook("black");
                int K = positionToIndexInString(
                    allChessPieces[castling.first]->position);
                int R = positionToIndexInString(
                    allChessPieces[castling.second]->position);
                QString newPosition =
                    translator->stringMove(allPositions.last(), K, 62);
                newPosition = translator->stringMove(newPosition, R, 61);
                allPositions.append(newPosition);
            }
        } else if (moves[i] == "0-0-0") {
            if ((i + 1) % 2 == 1) {
                QPair<int, int> castling = findKingAndRook("white", true);
                int K = positionToIndexInString(
                    allChessPieces[castling.first]->position);
                int R = positionToIndexInString(
                    allChessPieces[castling.second]->position);
                QString newPosition =
                    translator->stringMove(allPositions.last(), K, 2);
                newPosition = translator->stringMove(newPosition, R, 3);
                allPositions.append(newPosition);
            } else if ((i + 1) % 2 == 0) {
                QPair<int, int> castling = findKingAndRook("black", true);
                int K = positionToIndexInString(
                    allChessPieces[castling.first]->position);
                int R = positionToIndexInString(
                    allChessPieces[castling.second]->position);
                QString newPosition =
                    translator->stringMove(allPositions.last(), K, 59);
                newPosition = translator->stringMove(newPosition, R, 60);
                allPositions.append(newPosition);
            }
        } else if (pieces.contains(moves[i][moves[i].size() - 1])) {
            QPair<QPointF, QPointF> from_to =
                chessNotation->getFromAndToPos(moves[i]);
            int from = positionToIndexInString(from_to.first);
            int to = positionToIndexInString(from_to.second);
            QString newPosition =
                translator->stringMove(allPositions.last(), from, to);
            if ((i + 1) % 2 == 1)
                newPosition[to] = moves[i][moves[i].size() - 1].toLower();
            else if ((i + 1) % 2 == 0)
                newPosition[to] = moves[i][moves[i].size() - 1].toUpper();
            allPositions.append(newPosition);
        } else {
            QPair<QPointF, QPointF> from_to =
                chessNotation->getFromAndToPos(moves[i]);
            int from = positionToIndexInString(from_to.first);
            int to = positionToIndexInString(from_to.second);
            QString newPosition =
                translator->stringMove(allPositions.last(), from, to);

            if (moves[i].size() == 5 && moves[i][2] == 'x')
                newPosition[to - 8] = '-';

            allPositions.append(newPosition);
        }
    }
}

QPair<int, int> ReadOnlyMode::findKingAndRook(QString color, bool isLong) {
    QPair<int, int> result = qMakePair(-1, -1);
    int indexOfKing = -1;
    int indexOfRook = -1;
    QList<int> indexesOfRooks;
    QList<int> bestRooks;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->getColor() == color) {
            if (allChessPieces[i]->getName() == "King") {
                indexOfKing = i;
            } else if (allChessPieces[i]->getName() == "Rook") {
                indexesOfRooks.append(i);
            }
        }
    }
    if (indexesOfRooks.isEmpty() || indexOfKing == -1) {
        return result;
    }
    if (isLong) {
        for (int i = 0; i < indexesOfRooks.size(); i++) {
            if ((allChessPieces[indexesOfRooks[i]]->position.x() <
                 allChessPieces[indexOfKing]->position.x()) &&
                (allChessPieces[indexesOfRooks[i]]->position.y() ==
                 allChessPieces[indexOfKing]->position.y()))
                bestRooks.append(indexesOfRooks[i]);
        }
        if (bestRooks.isEmpty()) {
            return result;
        }
        if (bestRooks.size() > 1) {
            QList<int> allX;
            for (int i = 0; i < bestRooks.size(); i++) {
                allX.append(allChessPieces[bestRooks[i]]->position.x());
            }
            int bestX = *std::max_element(allX.begin(), allX.end());
            indexOfRook = bestRooks[allX.indexOf(bestX)];
        } else
            indexOfRook = bestRooks[0];
    } else {
        for (int i = 0; i < indexesOfRooks.size(); i++) {
            if ((allChessPieces[indexesOfRooks[i]]->position.x() >
                 allChessPieces[indexOfKing]->position.x()) &&
                (allChessPieces[indexesOfRooks[i]]->position.y() ==
                 allChessPieces[indexOfKing]->position.y()))
                bestRooks.append(indexesOfRooks[i]);
        }
        if (bestRooks.isEmpty()) {
            return result;
        }
        if (bestRooks.size() > 1) {
            QList<int> allX;
            for (int i = 0; i < bestRooks.size(); i++) {
                allX.append(allChessPieces[bestRooks[i]]->position.x());
            }
            int bestX = *std::min_element(allX.begin(), allX.end());
            indexOfRook = bestRooks[allX.indexOf(bestX)];
        } else
            indexOfRook = bestRooks[0];
    }
    result = qMakePair(indexOfKing, indexOfRook);
    return result;
}

int ReadOnlyMode::positionToIndexInString(QPointF pos) {
    int result;
    if (pos.x() < 0 || pos.x() > 7 * cellSize || pos.y() < 0 ||
        pos.y() > 7 * cellSize)
        return result;
    int x = pos.x() / cellSize;
    int y = pos.y() / cellSize;
    result = (7 - y) * 8 + x;
    return result;
}
