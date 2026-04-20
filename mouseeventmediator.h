#ifndef MOUSEEVENTMEDIATOR_H
#define MOUSEEVENTMEDIATOR_H
#include <QPointF>

class MouseEventMediator {
   public:
    QPointF getCell() const { return pieceMoveTo; }
    int getIndex() const { return indexOfLastButton; }
    int getIndexOfTakingOnPassage() const { return indexOfTakingOnPassage; }
    static MouseEventMediator* getInstance();
    void updateCell(QPointF coordinates);
    void updateIndex(int i);
    void updateIndexOfTakingOnPassage(int i);

   private:
    static MouseEventMediator* instance;
    MouseEventMediator();
    QPointF pieceMoveTo = QPointF(-1, -1);
    int indexOfLastButton = -1;
    int indexOfTakingOnPassage = -1;
};

#endif	// MOUSEEVENTMEDIATOR_H
