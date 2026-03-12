#include "chesspiece.h"

ChessPiece::ChessPiece() {}

bool ChessPiece::isWhite() const {
    return color == "white";
}

bool ChessPiece::isBlack() const {
    return color == "black";
}
