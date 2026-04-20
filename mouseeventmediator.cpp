#include "mouseeventmediator.h"

MouseEventMediator* MouseEventMediator::instance = nullptr;
MouseEventMediator::MouseEventMediator() {}

MouseEventMediator* MouseEventMediator::getInstance() {
    if (!instance) {
        instance = new MouseEventMediator();
    }
    return instance;
}

void MouseEventMediator::updateCell(QPointF coordinates) {
    pieceMoveTo = coordinates;
}

void MouseEventMediator::updateIndex(int i) {
    indexOfLastButton = i;
}

void MouseEventMediator::updateIndexOfTakingOnPassage(int i) {
    indexOfTakingOnPassage = i;
}
