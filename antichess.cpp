#include "antichess.h"
#include <QDebug>
#include <QMessageBox>

void AntiChess::ChessPieceManager() {
    QString startPosition =
        "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
    allChessPieces = translator->decryption(startPosition);
    for (int i = 0; i < 32; i++) {
        allChessPieceButtons.append(
            newBoard->addToChessboard(allChessPieces[i]));
    }
    enableCastling(4, 0);
    enableCastling(4, 7);
    enableCastling(28, 24);
    enableCastling(28, 31);
    updateCoordinates();
    for (int i = 0; i < allChessPieceButtons.size(); i++) {
        connect(allChessPieceButtons[i], &QPushButton::clicked,
                [this, i]() { chessPieceConnection(i); });
    }
    startGame();
}

void AntiChess::checkForTaking() {
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (isCanMove(i)) {
            GameMode::getPossibleMoves(i);
            if (!canBeTakenPieces.isEmpty()) {
                isMustBeTaking = true;
                canBeTakenPieces.clear();
                return;
            }
        }
    }
    isMustBeTaking = false;
}

QList<QPointF> AntiChess::getPossibleMoves(int index) {
    checkForTaking();
    QList<QPointF> possibleMoves = GameMode::getPossibleMoves(index);
    if (!isMustBeTaking)
        return possibleMoves;
    else {
        for (int i = possibleMoves.size() - 1; i >= 0; i--) {
            if (!canBeTakenPieces.contains(possibleMoves[i]))
                possibleMoves.removeAt(i);
        }
        return possibleMoves;
    }
}

bool AntiChess::whiteWin() {
    int counterOfWhitePieces = 0;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->position != QPointF(-1, -1) &&
            allChessPieces[i]->isWhite())
            counterOfWhitePieces++;
        if (counterOfWhitePieces > 1)
            return false;
    }
    return true;
}

bool AntiChess::blackWin() {
    int counterOfBlackPieces = 0;
    for (int i = 0; i < allChessPieces.size(); i++) {
        if (allChessPieces[i]->position != QPointF(-1, -1) &&
            allChessPieces[i]->isBlack())
            counterOfBlackPieces++;
        if (counterOfBlackPieces > 1)
            return false;
    }
    return true;
}

void AntiChess::gameOver() {
    if (counterOfMoves % 2 == 1) {
        if (isCheckMateForWhite()) {
            QMessageBox::information(newBoard->view, "Победа белых!",
                                     "Белым объявлен мат!");
        } else if (isStaleMateForWhite()) {
            QMessageBox::information(newBoard->view, "Ничья!",
                                     "Белым поставили пат!");
        }
    } else if (counterOfMoves % 2 == 0) {
        if (isCheckMateForBlack()) {
            QMessageBox::information(newBoard->view, "Победа чёрных!",
                                     "Чёрным объявлен мат!");
        } else if (isStaleMateForBlack()) {
            QMessageBox::information(newBoard->view, "Ничья!",
                                     "Чёрным поставили пат!");
        }
    }

    if (whiteWin()) {
        QMessageBox::information(newBoard->view, "Победа белых!",
                                 "Белые отдали все фигуры!");
        disableAllButtons();
    } else if (blackWin()) {
        QMessageBox::information(newBoard->view, "Победа чёрных!",
                                 "Чёрные отдали все фигуры!");
        disableAllButtons();
    }
}
