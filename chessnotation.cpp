#include "chessnotation.h"
#include <QDebug>

void ChessNotation::writeMove(QPointF from, QPointF to, QString name,
                              bool isTaking, QString pawnConvertTo,
                              int cellSize) {
    getCurrentTablePos();
    QString piece = lang->getChar(name);
    QString newPiece = lang->getChar(pawnConvertTo);
    QString left = getTextFromCell(from, cellSize);
    QString right = getTextFromCell(to, cellSize);
    QString sign = isTaking ? "x" : "-";
    QString move = piece + left + sign + right + newPiece;
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(move);
    notation->setItem(nowRow, nowCol, item);
}

void ChessNotation::writeCastling(bool isLong) {
    getCurrentTablePos();
    QString move = isLong ? "0-0-0" : "0-0";
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(move);
    notation->setItem(nowRow, nowCol, item);
}

void ChessNotation::writeString(QString str) {
    getCurrentTablePos();
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(str);
    notation->setItem(nowRow, nowCol, item);
}

void ChessNotation::getCurrentTablePos() {
    int rows = notation->rowCount();
    int columns = notation->columnCount();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QTableWidgetItem* item = notation->item(row, col);
            if (item == nullptr || item->text().isEmpty()) {
                nowRow = row;
                nowCol = col;
                return;
            }
        }
    }
    notation->setRowCount(rows + 1);
    notation->scrollToBottom();
    nowRow = rows;
    nowCol = 0;
}

QString ChessNotation::getTextFromCell(QPointF cell, int cellSize) {
    QString result = "--";
    int x = cell.x();
    int y = cell.y();
    QString allCells = "abcdefgh";
    QString allNumbers = "12345678";
    result[0] = allCells[x / cellSize];
    result[1] = allNumbers[7 - y / cellSize];
    return result;
}

QList<QString> ChessNotation::getMovesFromNotation() {
    QList<QString> result;
    int rows = notation->rowCount();
    int columns = notation->columnCount();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QTableWidgetItem* item = notation->item(row, col);
            if (item != nullptr && !item->text().isEmpty()) {
                result.append(item->text());
            }
        }
    }
    return result;
}
