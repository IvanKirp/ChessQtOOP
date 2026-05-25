#ifndef CHESSNOTATION_H
#define CHESSNOTATION_H
#include <QTableWidget>
#include "inotation.h"

class ChessNotation {
   public:
    ChessNotation(QTableWidget* notation, INotation* lang)
        : notation(notation), lang(lang) {}

    void showNotation() { notation->show(); }
    void hideNotation() { notation->hide(); }
    void writeMove(QPointF from, QPointF to, QString name,
                   bool isTaking = false, QString pawnConvertTo = "",
                   int cellSize = 100);
    void writeCastling(bool isLong = false);
    QList<QString> getMovesFromNotation();

   protected:
    QTableWidget* notation;
    INotation* lang;
    int nowRow, nowCol;	 //первая пустая ячейка

    void getCurrentTablePos();
    QString getTextFromCell(QPointF cell, int cellSize);
};

#endif	// CHESSNOTATION_H
