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
    view->show();

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

void GameScene::showStopButtons() {
    giveUpButton->setGeometry(850, 640, 100, 50);
    giveUpButton->show();

    drawButton->setGeometry(970, 640, 100, 50);
    drawButton->show();

    homeButton->setGeometry(850, 740, 220, 50);
    homeButton->show();
}

void GameScene::hideStopButtons() {}

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
                mousePressedToMove();
                break;
            }
        }
        newBoard->deletePossibleMoves();
    } else {
        QPointF scene_pos = event->scenePos();
        QPointF pieceMoveTo;
        pieceMoveTo = QPointF(
            scene_pos.x() - int(scene_pos.x()) % int(newBoard->cellSize),
            scene_pos.y() - int(scene_pos.y()) % int(newBoard->cellSize));
        mouseEventMediator->updateCell(pieceMoveTo);
        mousePressedToChoose();
    }
}
