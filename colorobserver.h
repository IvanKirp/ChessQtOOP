#ifndef COLOROBSERVER_H
#define COLOROBSERVER_H

#include <QList>
#include <QPushButton>

class ColorObserver {
   public:
    ColorObserver();

    void setNewColor(QList<QPushButton*> buttons, QList<QString> colors,
                     int counterOfMoves, bool isGameOver);
};

#endif	// COLOROBSERVER_H
