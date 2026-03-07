#include "scene.h"
#include "chessboard.h"

void Scene::drawScene() {
    scene->clear();
    view->setFixedSize(800, 800);
    view->setFocusPolicy(Qt::NoFocus);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    newBoard->drawChessboard();

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
