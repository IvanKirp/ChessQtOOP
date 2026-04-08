#ifndef MOUSEEVENTMEDIATOR_H
#define MOUSEEVENTMEDIATOR_H
#include <QPointF>

class MouseEventMediator {
   public:
    QPointF pieceMoveTo;
    static MouseEventMediator* getInstance();
    void updateCell(QPointF coordinates);

   private:
    static MouseEventMediator* instance;
    MouseEventMediator();
};

#endif	// MOUSEEVENTMEDIATOR_H
