#include "antichess.h"
#include <QDebug>

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
