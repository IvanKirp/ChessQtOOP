#include "queen.h"
#include "bishop.h"
#include "rook.h"

QList<QPointF> Queen::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> queenPossibleMoves_;

    int x = position.x();
    int y = position.y();

    Bishop* helpBishop = new Bishop(QPointF(x, y), color);
    Rook* helpRook = new Rook(QPointF(x, y), color);

    queenPossibleMoves_.append(helpBishop->possibleMoves(
        cellSize, coordinatesOfAllPieces, coordinatesOfWhitePieces,
        coordinatesOfBlackPieces));
    queenPossibleMoves_.append(helpRook->possibleMoves(
        cellSize, coordinatesOfAllPieces, coordinatesOfWhitePieces,
        coordinatesOfBlackPieces));

    delete helpBishop;
    delete helpRook;
    helpBishop = nullptr;
    helpRook = nullptr;

    return queenPossibleMoves_;
}
