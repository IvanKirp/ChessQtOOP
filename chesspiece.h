#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QPointF>
#include <QString>
class ChessPiece {
   public:
    QPointF position;
    QString color;

    ChessPiece();
    ChessPiece(QPointF position, QString color)
        : position(position), color(color) {}

    bool isWhite();
    bool isBlack();
    virtual QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces, int counterOfMoves) const = 0;
};

#endif	// CHESSPIECE_H
