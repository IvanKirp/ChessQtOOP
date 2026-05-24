#include "internationalnotation.h"

InternationalNotation::InternationalNotation() {}

QString InternationalNotation::getChar(QString name) {
    QString result;
    if (name == "Pawn")
        result = "";
    else if (name == "Rook")
        result = "R";
    else if (name == "Knight")
        result = "N";
    else if (name == "Bishop")
        result = "B";
    else if (name == "Queen")
        result = "Q";
    else if (name == "King")
        result = "K";
    return result;
}
