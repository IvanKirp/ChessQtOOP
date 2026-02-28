#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>

class Scene {
   public:
    Scene();

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene(QGraphicsScene* scene, QGraphicsView* view,
                   QTableWidget* notation);
};

#endif	// SCENE_H
