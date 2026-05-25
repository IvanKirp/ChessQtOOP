#include "threechecks.h"
#include <QDebug>
#include <QMessageBox>

void ThreeChecks::ChessPieceManager() {
    startPosition =
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

void ThreeChecks::updateCountersOfCheck() {
    if (isCheckForWhiteKing())
        counterOfChecksToWhite++;
    else if (isCheckForBlackKing())
        counterOfChecksToBlack++;
}

void ThreeChecks::updateCoordinates() {
    GameMode::updateCoordinates();
    updateCountersOfCheck();
}

void ThreeChecks::gameOver() {
    if (counterOfChecksToWhite == 3) {
        QMessageBox::information(newBoard->view, "Победа чёрных!",
                                 "Белым объявили три шаха!");
        disableAllButtons();
        isGameOver = true;
        result = "0:1";
    } else if (counterOfChecksToBlack == 3) {
        QMessageBox::information(newBoard->view, "Победа белых!",
                                 "Чёрным объявили три шаха!");
        disableAllButtons();
        isGameOver = true;
        result = "1:0";
    }
    GameMode::gameOver();
}
