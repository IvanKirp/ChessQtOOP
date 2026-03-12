#include "rook.h"

#include <QList>

QList<QPointF> Rook::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> rookPossibleMoves_;
    QList<QPointF> helpCoordinates = {
        QPointF(0, -cellSize), QPointF(0, cellSize), QPointF(cellSize, 0),
        QPointF(-cellSize, 0)};

    int x = position.x();
    int y = position.y();
    int newX;
    int newY;

    for (int k = 0; k < 4; k++) {
        for (int i = 1; i < 8; i++) {
            newX = x + i * helpCoordinates[k].x();
            newY = y + i * helpCoordinates[k].y();
            if (newX >= 0 && newX <= 7 * cellSize && newY >= 0 &&
                newY <= 7 * cellSize) {
                if (!coordinatesOfAllPieces.contains(QPointF(newX, newY))) {
                    rookPossibleMoves_.append(QPointF(newX, newY));
                } else {
                    if (isWhite() && coordinatesOfBlackPieces.contains(
                                         QPointF(newX, newY))) {
                        rookPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else if (isBlack() && coordinatesOfWhitePieces.contains(
                                                QPointF(newX, newY))) {
                        rookPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else
                        break;
                }
            }
        }
    }
    return rookPossibleMoves_;
}
