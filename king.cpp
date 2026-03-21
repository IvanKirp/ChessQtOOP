#include "king.h"

QList<QPointF> King::possibleMoves(
    int cellSize, QList<QPointF> coordinatesOfAllPieces,
    QList<QPointF> coordinatesOfWhitePieces,
    QList<QPointF> coordinatesOfBlackPieces) const {
    QList<QPointF> kingPossibleMoves_;
    QList<QPointF> helpCoordinates = {
        QPointF(-cellSize, -cellSize), QPointF(-cellSize, 0),
        QPointF(-cellSize, cellSize),  QPointF(0, cellSize),
        QPointF(0, -cellSize),		   QPointF(cellSize, -cellSize),
        QPointF(cellSize, 0),		   QPointF(cellSize, cellSize)};

    int x = position.x();
    int y = position.y();
    int newX;
    int newY;
    //добавить в параметры метода QList<QPointF> KingCanNotMove, где будут все поля под боем вражеских фигур и все поля, где стоят защищённые фигуры
    //добавить класс для рисования кружочков (отметка ходов), использующий НЕстатический метод, чтобы для удаления кружочков можно было просто вызввать деструктор класса
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 1; k++) {
            newX = x + helpCoordinates[i].x();
            newY = y + helpCoordinates[i].y();
            if (newX >= 0 && newX <= 7 * cellSize && newY >= 0 &&
                newY <= 7 * cellSize) {
                if (!coordinatesOfAllPieces.contains(QPointF(newX, newY))) {
                    kingPossibleMoves_.append(QPointF(newX, newY));
                } else {
                    if (isWhite() && coordinatesOfBlackPieces.contains(
                                         QPointF(newX, newY))) {
                        kingPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else if (isBlack() && coordinatesOfWhitePieces.contains(
                                                QPointF(newX, newY))) {
                        kingPossibleMoves_.append(QPointF(newX, newY));
                        break;
                    } else
                        break;
                }
            }
        }
    }
    return kingPossibleMoves_;
}
