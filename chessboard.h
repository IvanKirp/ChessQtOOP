#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "chesspiece.h"

class ChessBoard {
   public:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QList<QGraphicsEllipseItem*> circle;
    QList<QPushButton*> pawnChooseButtons;
    int cellSize;

    ChessBoard(QGraphicsScene* scene, QGraphicsView* view, int cellSize)
        : scene(scene), view(view), cellSize(cellSize) {}
    void drawChessboard();
    void drawPossibleMoves(QList<QPointF> coordinates);
    void deletePossibleMoves();
    QPushButton* addToChessboard(ChessPiece* piece, int cellSize = 100);
    void deleteFromChessboard(QPushButton* button);
    void addWhitePawnChooseButtons(QPointF moveTo);
    void addBlackPawnChooseButtons(QPointF moveTo);
    void deletePawnChooseButtons();
    void selectButton(QPushButton* button, QString color);
    void deleteAllSelections(QList<QPushButton*> allButtons);
};
#endif	// CHESSBOARD_H
