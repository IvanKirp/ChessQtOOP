#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QList>
#include <QPointF>
#include <QString>

class ChessPiece {
   public:
    QPointF position;

    ChessPiece();
    ChessPiece(QPointF position, QString color)
        : position(position), color(color) {}

    QString getName() const { return name; }
    QString getColor() const { return color; }
    bool isWhite() const;
    bool isBlack() const;
    virtual QList<QPointF> possibleMoves(
        int cellSize, QList<QPointF> coordinatesOfAllPieces,
        QList<QPointF> coordinatesOfWhitePieces,
        QList<QPointF> coordinatesOfBlackPieces) const = 0;

   protected:
    QString name;
    QString color;
};

#endif	// CHESSPIECE_H
