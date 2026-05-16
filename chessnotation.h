#ifndef CHESSNOTATION_H
#define CHESSNOTATION_H
#include <QTableWidget>

class ChessNotation {
   public:
    ChessNotation(QTableWidget* notation) : notation(notation) {}

    QTableWidget* notation;
};

#endif	// CHESSNOTATION_H
