#ifndef CHESSNOTATION_H
#define CHESSNOTATION_H
#include <QPair>
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
    void writeString(QString str);
    QList<QString> getMovesFromNotation();
    QPair<QPointF, QPointF> getFromAndToPos(QString move, int cellSize = 100);

    void right();
    void left();
    int currentMove = 0;

   protected:
    QTableWidget* notation;
    INotation* lang;
    int nowRow, nowCol;	 //первая пустая ячейка

    void getCurrentTablePos();
    QString getTextFromCell(QPointF cell, int cellSize);
    QPointF getCellFromText(QString text, int cellSize);
};

#endif	// CHESSNOTATION_H
