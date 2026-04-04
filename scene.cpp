#include "scene.h"
#include "chessboard.h"

void Scene::drawScene() {
    scene->clear();
    view->setFixedSize(800, 800);
    view->setFocusPolicy(Qt::NoFocus);
    view->setFocus();
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

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPointF pos = event->scenePos();
    qDebug() << "Position:" << pos;
    qDebug() << "Button:" << event->button();
    /*if (scene && !circle.isEmpty()) {
        QPointF scene_pos = view->mapToScene(event->pos());
        if (event->button() == Qt::RightButton) {
            deleteSelections();
            if (isCheck().first == true)
                drawCheck();
        }
        if (event->button() == Qt::LeftButton) {
            for (QGraphicsEllipseItem* ellipse : circle) {
                QPointF center = ellipse->scenePos() + QPointF(15, 15);
                QRectF clickableArea(center.x() - 50, center.y() - 50, 100,
                                     100);

                if (clickableArea.contains(scene_pos)) {
                    QPointF pieceMoveTo;
                    pieceMoveTo.setX(center.x() - 50);
                    pieceMoveTo.setY(center.y() - 50);
                    move(pieceMoveTo);
                    deleteSelections();
                    break;
                }
            }
            if (isCheck().first == true)
                drawCheck();
        }
    }*/
    emit mousePressed(pos, event->button());
    update();
    QGraphicsScene::mousePressEvent(event);
}
