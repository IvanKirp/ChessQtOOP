#ifndef SCENE_H
#define SCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>
#include "chessboard.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

   public:
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;

    Scene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
          QTableWidget* notation)
        : scene(scene), view(view), newBoard(newBoard), notation(notation) {
        if (view) {
            view->setMouseTracking(true);
        }
        setSceneRect(0, 0, 800, 800);
    }

    QPushButton *giveUpButton, *drawButton, *homeButton;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
   signals:
    void mousePressed(const QPointF& pos, Qt::MouseButton button);
};

#endif	// SCENE_H
