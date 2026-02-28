#include "scene.h"
#include "chessboard.h"

Scene::Scene() {}

void Scene::drawScene(QGraphicsScene* scene, QGraphicsView* view,
                      QTableWidget* notation) {
    scene->clear();
    view->setFixedSize(800, 800);
    view->setFocusPolicy(Qt::NoFocus);
    scene->setSceneRect(0, 0, 800, 800);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ChessBoard* newBoard = new ChessBoard();
    newBoard->drawChessboard(scene);

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
