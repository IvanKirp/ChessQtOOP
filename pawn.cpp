#include "pawn.h"

QList<QPointF> Pawn::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> pawnPossibleMoves_;
    QList<QPointF> helpCoordinates;

    int x = position.x();
    int y = position.y();
    int newX;
    int newY;

    if (isWhite()) {
        helpCoordinates = {QPointF(0, -cellSize), QPointF(-cellSize, -cellSize),
                           QPointF(cellSize, -cellSize)};
        if (y == 6 * cellSize &&
            !coordinatesOfAllPieces.contains(QPointF(x, y - cellSize)))
            helpCoordinates.append(QPointF(0, -2 * cellSize));
    } else if (isBlack()) {
        helpCoordinates = {QPointF(0, cellSize), QPointF(-cellSize, cellSize),
                           QPointF(cellSize, cellSize)};
        if (y == cellSize &&
            !coordinatesOfAllPieces.contains(QPointF(x, y + cellSize)))
            helpCoordinates.append(QPointF(0, 2 * cellSize));
    }

    for (int i = 0; i < helpCoordinates.size(); i++) {
        for (int k = 0; k < 1; k++) {
            newX = x + helpCoordinates[i].x();
            newY = y + helpCoordinates[i].y();
            if (newX >= 0 && newX <= 7 * cellSize && newY >= 0 &&
                newY <= 7 * cellSize) {
                if (!coordinatesOfAllPieces.contains(QPointF(newX, newY)) &&
                    x == newX) {
                    pawnPossibleMoves_.append(QPointF(newX, newY));
                } else {
                    if (isWhite() &&
                        coordinatesOfBlackPieces.contains(
                            QPointF(newX, newY)) &&
                        x != newX) {
                        pawnPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else if (isBlack() &&
                               coordinatesOfWhitePieces.contains(
                                   QPointF(newX, newY)) &&
                               x != newX) {
                        pawnPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else
                        break;
                }
            }
        }
    }
    return pawnPossibleMoves_;
}
