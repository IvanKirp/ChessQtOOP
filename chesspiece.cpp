#include "chesspiece.h"

ChessPiece::ChessPiece() {}

bool ChessPiece::isWhite() {
    return color == "white";
}

bool ChessPiece::isBlack() {
    return color == "black";
}
