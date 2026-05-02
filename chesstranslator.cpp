#include "chesstranslator.h"
#include <QDebug>
#include "chesspiece.h"
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

QList<QPair<QPointF, QString>> ChessTranslator::decryption(QString code,
                                                           int cellSize) {
    QList<QPair<QPointF, QString>> result;

    for (int i = 0; i < code.size(); i++) {
        if (code[i] != "-") {
            int x = i % 8;
            int y = 7 - i / 8;
            QPointF cell = QPointF(x * cellSize, y * cellSize);

            QString piece;
            if (code[i] == code[i].toLower())
                piece = QString("w") + QString(code[i]);
            else if (code[i] == code[i].toUpper())
                piece = QString("b") + QString(code[i].toLower());

            result.append(qMakePair(cell, piece));
        }
    }
    return result;
}
