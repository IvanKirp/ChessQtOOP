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

QPair<QPointF, QPointF> ChessNotation::getFromAndToPos(QString move,
                                                       int cellSize) {
    QPair<QPointF, QPointF> result;
    QString from, to;
    QPointF fromPos, toPos;

    if (move.size() == 5) {
        from.append(move[0]);
        from.append(move[1]);
        to.append(move[3]);
        to.append(move[4]);
    } else if (move.size() == 6) {
        from.append(move[1]);
        from.append(move[2]);
        to.append(move[4]);
        to.append(move[5]);
    }

    fromPos = getCellFromText(from, cellSize);
    toPos = getCellFromText(to, cellSize);
    result = qMakePair(fromPos, toPos);
    return result;
}

QPointF ChessNotation::getCellFromText(QString text, int cellSize) {
    QPointF result;
    QString allCells = "abcdefgh";
    QString allNumbers = "12345678";
    int x = allCells.indexOf(text[0]) * cellSize;
    int y = (7 - allNumbers.indexOf(text[1])) * cellSize;
    result = QPointF(x, y);
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

void ChessNotation::right() {
    int currentRow = notation->currentRow();
    int currentCol = notation->currentColumn();

    if (currentRow == -1 && currentCol == -1) {
        notation->setCurrentCell(0, 0);
        currentMove = 0;
        return;
    }

    int newRow = currentRow;
    int newCol = currentCol + 1;

    if (newCol >= notation->columnCount()) {
        newCol = 0;
        newRow++;
    }

    if (newRow >= notation->rowCount()) {
        return;
    }

    QTableWidgetItem* item = notation->item(newRow, newCol);
    if (item && !item->text().isEmpty() && item->text() != " ") {
        notation->setCurrentCell(newRow, newCol);
        currentMove = 2 * newRow + newCol;
    }
}

void ChessNotation::left() {
    int currentRow = notation->currentRow();
    int currentCol = notation->currentColumn();

    if (currentRow == -1 && currentCol == -1) {
        return;
    }

    if (currentRow == 0 && currentCol == 0) {
        notation->setCurrentCell(-1, -1);
        notation->clearSelection();
        currentMove = -1;
        return;
    }

    int newRow = currentRow;
    int newCol = currentCol - 1;

    if (newCol < 0) {
        newCol = notation->columnCount() - 1;
        newRow--;
    }

    if (newRow < 0) {
        return;
    }

    notation->setCurrentCell(newRow, newCol);
    currentMove = 2 * newRow + newCol;
}
