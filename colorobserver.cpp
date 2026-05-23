#include "colorobserver.h"
#include <QDebug>
ColorObserver::ColorObserver() {}

void ColorObserver::setNewColor(QList<QPushButton*> buttons,
                                QList<QString> colors, int counterOfMoves,
                                bool isGameOver) {
    qDebug() << "counterOfMoves" << counterOfMoves;
    if (buttons.size() != colors.size())
        return;
    if (isGameOver) {
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i]->setStyleSheet("background: transparent; border: none;");
        }
    } else {
        if (counterOfMoves % 2 == 1) {
            for (int i = 0; i < buttons.size(); i++) {
                if (colors[i] == "white") {
                    buttons[i]->setStyleSheet(
                        "QPushButton {"
                        "   background-color: transparent;"
                        "   color: transparent;"
                        "   border: none;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: green;"
                        "   color: transparent;}");
                } else if (colors[i] == "black") {
                    buttons[i]->setStyleSheet(
                        "background: transparent; border: none;");
                }
            }
        } else if (counterOfMoves % 2 == 0) {
            for (int i = 0; i < buttons.size(); i++) {
                if (colors[i] == "black") {
                    buttons[i]->setStyleSheet(
                        "QPushButton {"
                        "   background-color: transparent;"
                        "   color: transparent;"
                        "   border: none;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: green;"
                        "   color: transparent;}");
                } else if (colors[i] == "white") {
                    buttons[i]->setStyleSheet(
                        "background: transparent; border: none;");
                }
            }
        }
    }
}
