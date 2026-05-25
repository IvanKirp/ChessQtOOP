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
    startGame();
}
