#include "fischerchess.h"

void FischerChess::ChessPieceManager() {
    QString startPosition = getStartPosition(numberOfPosition);
    allChessPieces = translator->decryption(startPosition);
    for (int i = 0; i < 32; i++) {
        allChessPieceButtons.append(
            newBoard->addToChessboard(allChessPieces[i]));
    }

    int indexOfWhiteKing, indexOfBlackKing;
    for (int i = 0; i < 32; i++) {
        if (dynamic_cast<King*>(allChessPieces[i])) {
            if (allChessPieces[i]->isWhite())
                indexOfWhiteKing = i;
            else if (allChessPieces[i]->isBlack())
                indexOfBlackKing = i;
        }
    }
    for (int i = 0; i < 32; i++) {
        if (dynamic_cast<Rook*>(allChessPieces[i])) {
            if (allChessPieces[i]->isWhite())
                enableCastling(indexOfWhiteKing, i);
            else if (allChessPieces[i]->isBlack())
                enableCastling(indexOfBlackKing, i);
        }
    }

    updateCoordinates();

    for (int i = 0; i < allChessPieceButtons.size(); i++) {
        connect(allChessPieceButtons[i], &QPushButton::clicked,
                [this, i]() { chessPieceConnection(i); });
    }
}

QString FischerChess::getStartPosition(int number) {
    number--;
    if ((number < 0) || (number > 960))
        return "";

    QList<QString> all960Positions;
    QList<QString> permutations;
    /*
    0 - rook
    1 - knight
    2 - bishop
    3 - queen
    4 - king
    5 - bishop
    6 - knight
    7 - rook
    */
    QString pieces = "rnbqkbnr";
    QString s = "01234567";

    do {
        if ((s.indexOf("2") + s.indexOf("5")) % 2 == 1 &&
            s.indexOf("7") > s.indexOf("4") &&
            s.indexOf("0") < s.indexOf("4")) {
            permutations.append(s);
        }
    } while (std::next_permutation(s.begin(), s.end()));

    for (int i = 0; i < permutations.size(); i++) {
        QString pos = "--------";
        for (int j = 0; j < 8; j++) {
            pos[j] = pieces[QString(permutations[i][j]).toInt()];
        }

        if (!all960Positions.contains(pos))
            all960Positions.append(pos);
    }

    QString whitePieces = all960Positions[number];
    QString blackPieces = whitePieces.toUpper();
    QString middle;
    for (int i = 0; i < 32; i++) {
        middle.append("-");
    }
    QString whitePawns, blackPawns;
    for (int i = 0; i < 8; i++) {
        whitePawns.append("p");
        blackPawns.append("P");
    }
    QString result =
        whitePieces + whitePawns + middle + blackPawns + blackPieces;
    return result;
}
