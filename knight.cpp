#include "knight.h"

QList<QPointF> Knight::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> knightPossibleMoves_;
    QList<QPointF> helpCoordinates = {
        QPointF(cellSize, 2 * cellSize),  QPointF(cellSize, -2 * cellSize),
        QPointF(-cellSize, 2 * cellSize), QPointF(-cellSize, -2 * cellSize),
        QPointF(2 * cellSize, cellSize),  QPointF(2 * cellSize, -cellSize),
        QPointF(-2 * cellSize, cellSize), QPointF(-2 * cellSize, -cellSize)};

    int x = position.x();
    int y = position.y();
    int newX;
    int newY;

    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 1; k++) {
            newX = x + helpCoordinates[i].x();
            newY = y + helpCoordinates[i].y();
            if (newX >= 0 && newX <= 7 * cellSize && newY >= 0 &&
                newY <= 7 * cellSize) {
                if (!coordinatesOfAllPieces.contains(QPointF(newX, newY))) {
                    knightPossibleMoves_.append(QPointF(newX, newY));
                } else {
                    if (isWhite() && !coordinatesOfWhitePieces.contains(
                                         QPointF(newX, newY))) {
                        knightPossibleMoves_.append(QPointF(newX, newY));
                    } else if (isBlack() && !coordinatesOfBlackPieces.contains(
                                                QPointF(newX, newY))) {
                        knightPossibleMoves_.append(QPointF(newX, newY));
                    } else
                        break;
                }
            }
        }
    }

    return knightPossibleMoves_;
}
