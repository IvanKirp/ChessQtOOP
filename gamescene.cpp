#include "gamescene.h"
#include "QDebug"
#include "chessboard.h"
#include "gamemode.h"

void GameScene::drawScene() {
    scene->clear();
    view->setFixedSize(800, 800);
    view->setFocusPolicy(Qt::NoFocus);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    newBoard->drawChessboard();
    view->setMouseTracking(true);

    notation->setGeometry(850, 0, 223, 625);
    notation->setRowCount(20);
    notation->setColumnCount(2);
    notation->setEditTriggers(QAbstractItemView::NoEditTriggers);
    notation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    notation->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    notation->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    notation->setHorizontalHeaderLabels({"Белые", "Чёрные"});
    notation->show();
    notation->setFocusPolicy(Qt::NoFocus);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (scene && !newBoard->circle.isEmpty()) {
        int cellSize = newBoard->cellSize;
        double radius = cellSize * 0.3 / 2;
        QPointF scene_pos = event->scenePos();
        for (QGraphicsEllipseItem* ellipse : newBoard->circle) {
            QPointF center = ellipse->scenePos() + QPointF(radius, radius);
            QRectF clickableArea =
                QRectF(center.x() - cellSize / 2, center.y() - cellSize / 2,
                       cellSize, cellSize);
            if (clickableArea.contains(scene_pos)) {
                QPointF pieceMoveTo;
                pieceMoveTo = QPointF(center.x() - cellSize / 2,
                                      center.y() - cellSize / 2);
                mouseEventMediator->updateCell(pieceMoveTo);
                mousePressed();
                break;
            }
        }
        newBoard->deletePossibleMoves();
    }
}
