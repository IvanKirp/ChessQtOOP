#ifndef MOUSEEVENTMEDIATOR_H
#define MOUSEEVENTMEDIATOR_H
#include <QPointF>

class MouseEventMediator {
   public:
    QPointF getCell() const { return pieceMoveTo; }
    int getIndex() const { return indexOfLastButton; }
    //bool getIsCanMove() const { return isCanMove; }
    static MouseEventMediator* getInstance();
    void updateCell(QPointF coordinates);
    void updateIndex(int i);
    //void updateIsCanMove(bool condition);

   private:
    static MouseEventMediator* instance;
    MouseEventMediator();
    QPointF pieceMoveTo = QPointF(-1, 1);
    int indexOfLastButton = -1;
    //bool isCanMove = 0;
};

#endif	// MOUSEEVENTMEDIATOR_H
