#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHeaderView>
#include <QKeyEvent>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include "chessboard.h"
#include "mouseeventmediator.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT

   public:
    QWidget* window = nullptr;
    QGraphicsScene* scene;
    QGraphicsView* view;
    ChessBoard* newBoard;
    QTableWidget* notation;
    MouseEventMediator* mouseEventMediator = MouseEventMediator::getInstance();

    GameScene(QGraphicsScene* scene, QGraphicsView* view, ChessBoard* newBoard,
              QTableWidget* notation, QWidget* parent)
        : scene(scene),
          view(view),
          newBoard(newBoard),
          notation(notation),
          window(parent) {
        giveUpButton = new QPushButton("сдаться", window);
        giveUpButton->hide();
        drawButton = new QPushButton("ничья", window);
        drawButton->hide();
        homeButton = new QPushButton("Выйти в главное меню", window);
        homeButton->hide();
        text = new QTextEdit(window);
        text->hide();
        mouseEventMediator->setScene(this);
        mouseEventMediator->setConnection();
    }

    QPushButton *giveUpButton, *drawButton, *homeButton;
    QTextEdit* text;

    void drawScene();

   protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

   signals:
    void mousePressedToMove();
    void mousePressedToChoose();
    void left();
    void right();

   public slots:
    void showStopButtons();
    void hideStopButtons();
    void showReadOnlyMenu();
    void hideReadOnlyMenu();
};

#endif	// GAMESCENE_H
