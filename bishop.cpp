#include "bishop.h"

#include <QDebug>
#include <QList>
#include <QPair>

QList<QPointF> Bishop::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> bishopPossibleMoves_;
    QList<QPointF> helpCoordinates = {
        QPointF(cellSize, cellSize), QPointF(cellSize, -cellSize),
        QPointF(-cellSize, cellSize), QPointF(-cellSize, -cellSize)};

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
                    bishopPossibleMoves_.append(QPointF(newX, newY));
                } else if (color == "white" &&
                           coordinatesOfBlackPieces.contains(
                               QPointF(newX, newY))) {
                    bishopPossibleMoves_.append(QPointF(newX, newY));
                    break;
                } else if (color == "black" &&
                           coordinatesOfWhitePieces.contains(
                               QPointF(newX, newY))) {
                    bishopPossibleMoves_.append(QPointF(newX, newY));
                    break;
                } else
                    break;
            }
        }
    }
    qDebug() << color;
    return bishopPossibleMoves_;
}
