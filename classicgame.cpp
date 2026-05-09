#include "classicgame.h"
#include <QDebug>
#include "mouseeventmediator.h"

void ClassicGame::ChessPieceManager() {
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
    qDebug() << coordinatesOfAllPieces;
    qDebug() << isCheckForWhiteKing();
    qDebug() << isCheckForBlackKing();
    for (int i = 0; i < allChessPieceButtons.size(); i++) {
        connect(allChessPieceButtons[i], &QPushButton::clicked,
                [this, i]() { chessPieceConnection(i); });
    }

    qDebug() << translator->encryption(allChessPieces);
}
