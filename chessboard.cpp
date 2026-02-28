#include "chessboard.h"
#include <QPainter>
#include "mainwindow.h"

ChessBoard::ChessBoard() {}

QRectF ChessBoard::boundingRect() const {
    return QRectF(0, 0, 800, 800);
}

void ChessBoard::drawChessboard(QGraphicsScene* scene) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QColor color = ((row + col) % 2 == 0) ? QColor(240, 217, 181)
                                                  : QColor(181, 136, 99);

            QGraphicsRectItem* cell = new QGraphicsRectItem(
                col * cellSize, row * cellSize, cellSize, cellSize);

            cell->setBrush(QBrush(color));

            scene->addItem(cell);
        }
    }

    scene->setSceneRect(0, 0, 8 * cellSize, 8 * cellSize);
}
