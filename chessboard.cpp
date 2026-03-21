#include "chessboard.h"
#include "mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <typeinfo>

void ChessBoard::drawChessboard() {
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
}

QPushButton* ChessBoard::addToChessboard(ChessPiece* piece) {
    QString name = piece->getName();
    QString imagePath = ":/images/" + piece->getColor() + name + ".png";
    QPushButton* button = new QPushButton(view);
    button->setGeometry(piece->position.x(), piece->position.y(), cellSize,
                        cellSize);
    button->setIcon(QIcon(imagePath));
    button->setIconSize(QSize(cellSize, cellSize));
    button->setStyleSheet("background: transparent; border: none;");
    button->setFocusPolicy(Qt::NoFocus);
    return button;
}
