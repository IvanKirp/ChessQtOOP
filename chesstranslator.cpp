#include "chesstranslator.h"
#include <QMessageBox>
#include "bishop.h"
#include "chesspiece.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
ChessTranslator::ChessTranslator() {}

QString ChessTranslator::encryption(QList<ChessPiece*> allChessPieces,
                                    int cellSize) {
    QString result;
    for (int i = 0; i < 64; i++) {
        result.append("-");
    }

    QList<QPair<int, QString>> temp;
    for (int i = 0; i < allChessPieces.size(); i++) {
        int x = allChessPieces[i]->position.x();
        int y = allChessPieces[i]->position.y();

        QString shortName;
        if (allChessPieces[i]->getName() == "Knight")
            shortName = "N";
        else
            shortName = QString(allChessPieces[i]->getName()[0]);

        if (allChessPieces[i]->isWhite())
            shortName = shortName.toLower();
        else if (allChessPieces[i]->isBlack())
            shortName = shortName.toUpper();

        int index = x / cellSize + 8 * (7 - y / cellSize);

        temp.append(qMakePair(index, shortName));
    }

    for (int i = 0; i < temp.size(); i++) {
        result[temp[i].first] = temp[i].second[0];
    }

    return result;
}

QList<ChessPiece*> ChessTranslator::decryption(QString code, int cellSize) {
    QList<ChessPiece*> result;

    for (int i = 0; i < code.size(); i++) {
        if (code[i] != "-") {
            int x = i % 8;
            int y = 7 - i / 8;
            QPointF cell = QPointF(x * cellSize, y * cellSize);

            QString color;
            if (code[i] == code[i].toLower())
                color = "white";
            else if (code[i] == code[i].toUpper())
                color = "black";

            ChessPiece* piece;
            char p = code.toLower().toStdString()[i];
            switch (p) {
                case 'r':
                    piece = new Rook(cell, color, false);
                    result.append(piece);
                    break;
                case 'n':
                    piece = new Knight(cell, color);
                    result.append(piece);
                    break;
                case 'b':
                    piece = new Bishop(cell, color);
                    result.append(piece);
                    break;
                case 'q':
                    piece = new Queen(cell, color);
                    result.append(piece);
                    break;
                case 'k':
                    piece = new King(cell, color, false);
                    result.append(piece);
                    break;
                case 'p':
                    piece = new Pawn(cell, color, false);
                    result.append(piece);
                    break;
            }
        }
    }
    return result;
}

QString ChessTranslator::stringMove(QString str, int from, int to) {
    if (str.size() != 64 || from > 63 || to > 63 || from < 0 || to < 0)
        return str;
    str[to] = str[from];
    str[from] = '-';
    return str;
}
