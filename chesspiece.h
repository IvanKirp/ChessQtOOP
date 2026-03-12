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

    bool isWhite() const;
    bool isBlack() const;
    virtual QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const = 0;
};

#endif	// CHESSPIECE_H
