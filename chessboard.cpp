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
            cell->setAcceptedMouseButtons(Qt::NoButton);
            cell->setFlag(QGraphicsItem::ItemIsSelectable, false);
            cell->setFlag(QGraphicsItem::ItemIsMovable, false);
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

void ChessBoard::drawPossibleMoves(QList<QPointF> coordinates) {
    QColor color = QColor("green");
    for (int i = 0; i < coordinates.size(); i++) {
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(0, 0, 30, 30);
        ellipse->setPos(coordinates[i].x() + (cellSize / 2 - 15),
                        coordinates[i].y() + (cellSize / 2 - 15));
        circle.append(ellipse);
        circle[i]->setBrush(QBrush(color));
        circle[i]->setPen(Qt::NoPen);
        scene->addItem(circle[i]);
    }
}

void ChessBoard::deletePossibleMoves() {
    if (!circle.isEmpty()) {
        for (int i = 0; i < circle.size(); i++) {
            scene->removeItem(circle[i]);
            delete circle[i];
        }
        circle.clear();
    }
}
