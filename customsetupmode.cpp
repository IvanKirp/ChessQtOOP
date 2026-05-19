#include "customsetupmode.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

void CustomSetupMode::ChessPieceManager() {
    chessNotation->notation->hide();
    QList<QString> names = {"Pawn",	 "Knight", "Bishop", "Rook",
                            "Queen", "King",   "King",	 "Queen",
                            "Rook",	 "Bishop", "Knight", "Pawn"};
    QList<QString> colors = {"white", "white", "white", "white",
                             "white", "white", "black", "black",
                             "black", "black", "black", "black"};
    for (int i = 0; i < 16; i++) {
        if (i < 12) {
            QString imagePath = ":/images/" + colors[i] + names[i] + ".png";
            choosePieceButtons[i]->setIcon(QIcon(imagePath));
            choosePieceButtons[i]->setIconSize(QSize(cellSize, cellSize));
            choosePieceButtons[i]->setStyleSheet(
                "background: transparent; border: none;");
            choosePieceButtons[i]->setFocusPolicy(Qt::NoFocus);
            choosePieceButtons[i]->setStyleSheet(
                "QPushButton:hover {"
                "   background-color: green;"
                "   color: rgb(234, 255, 3);}");
            choosePieceButtons[i]->show();
            connect(choosePieceButtons[i], &QPushButton::clicked, [this, i]() {
                isDeleting = false;
                lastChoosenPiece = i;
            });
        } else if (i >= 12) {
            choosePieceButtons[i]->setStyleSheet(
                "QPushButton:hover {"
                "   background-color: red;"
                "   color: rgb(234, 255, 3);}");
            choosePieceButtons[i]->show();
        }
    }

    connect(choosePieceButtons[12], &QPushButton::clicked, [this]() {
        isDeleting = true;
        setCastling = false;
        setTakingOnPassage = false;
        lastChoosenPiece = -1;
    });

    connect(choosePieceButtons[13], &QPushButton::clicked, [this]() {
        for (int i = 0; i < choosenPieceButtons.size(); i++) {
            if (choosenPieceButtons[i]) {
                allChessPieces.append(choosenPieces[i]);
                allChessPieceButtons.append(choosenPieceButtons[i]);
            }
        }
        updateCoordinates();

        int counterOfWhiteKings = 0;
        int counterOfBlackKings = 0;
        bool badPawn = false;

        qDebug() << allChessPieces.size();
        for (int i = 0; i < allChessPieces.size(); i++) {
            if (allChessPieces[i]->getName() == "King" &&
                allChessPieces[i]->isWhite())
                counterOfWhiteKings++;
            else if (allChessPieces[i]->getName() == "King" &&
                     allChessPieces[i]->isBlack())
                counterOfBlackKings++;
            if (allChessPieces[i]->getName() == "Pawn" &&
                (allChessPieces[i]->position.y() == 0 ||
                 allChessPieces[i]->position.y() == 7 * cellSize))
                badPawn = true;
        }
        qDebug() << counterOfWhiteKings;
        qDebug() << counterOfBlackKings;
        if (counterOfWhiteKings != 1 || counterOfBlackKings != 1) {
            clearAllLists();
            QMessageBox::warning(newBoard->view, "Ошибка",
                                 "Неверное количество\nкоролей на доске!");
            return;
        }
        if (badPawn == true) {
            clearAllLists();
            QMessageBox::warning(newBoard->view, "Ошибка",
                                 "Неверное положение\nпешек на доске!");
            return;
        }

        isDeleting = false;
        setCastling = false;
        setTakingOnPassage = false;
        lastChoosenPiece = -1;

        bool ok;
        QStringList items;
        items << "ход белых" << "ход чёрных";
        QString startColor = QInputDialog::getItem(newBoard->view, "Чей ход?",
                                                   "Выберите очерёдность хода",
                                                   items, 0, false, &ok);
        if (ok) {
            if (startColor == "ход белых")
                counterOfMoves = 1;
            else if (startColor == "ход чёрных")
                counterOfMoves = 2;
        }

        if ((isCheckForWhiteKing() && counterOfMoves == 2) ||
            (isCheckForBlackKing() && counterOfMoves == 1)) {
            clearAllLists();
            QMessageBox::warning(newBoard->view, "Ошибка",
                                 "Некорректная позиция");
            return;
        }

        for (int i = 0; i < allChessPieceButtons.size(); i++) {
            connect(allChessPieceButtons[i], &QPushButton::clicked,
                    [this, i]() { chessPieceConnection(i); });
        }

        for (int i = 0; i < choosePieceButtons.size(); i++) {
            choosePieceButtons[i]->hide();
        }
    });

    connect(choosePieceButtons[14], &QPushButton::clicked, [this]() {
        setCastling = true;
        setTakingOnPassage = false;
        isDeleting = false;
        lastChoosenPiece = -1;
    });

    connect(choosePieceButtons[15], &QPushButton::clicked, [this]() {
        isDeleting = false;
        setCastling = false;
        setTakingOnPassage = true;
        lastChoosenPiece = -1;
    });
}

void CustomSetupMode::addPiece() {
    if (lastChoosenPiece == -1)
        return;
    QPointF position = mouseEventMediator->getCell();
    QString color;
    int i = lastChoosenPiece;
    if (i < 6)
        color = "white";
    else if (i >= 6)
        color = "black";

    if (i == 0 || i == 11)
        choosenPieces.append(new Pawn(position, color, false));
    else if (i == 1 || i == 10)
        choosenPieces.append(new Knight(position, color));
    else if (i == 2 || i == 9)
        choosenPieces.append(new Bishop(position, color));
    else if (i == 3 || i == 8)
        choosenPieces.append(new Rook(position, color, false));
    else if (i == 4 || i == 7)
        choosenPieces.append(new Queen(position, color));
    else if (i == 5 || i == 6)
        choosenPieces.append(new King(position, color, false));

    choosenPieceButtons.append(newBoard->addToChessboard(choosenPieces.last()));
    int indexOfButton = choosenPieceButtons.size() - 1;
    int indexOfPiece = choosenPieces.size() - 1;
    connect(
        choosenPieceButtons[indexOfButton], &QPushButton::clicked,
        [this, indexOfButton, indexOfPiece]() {
            if (isDeleting == true) {
                newBoard->deleteFromChessboard(
                    choosenPieceButtons[indexOfButton]);
                choosenPieceButtons[indexOfButton] = nullptr;
                return;
            }
            if (setCastling == true) {
                if (dynamic_cast<King*>(choosenPieces[indexOfPiece])) {
                    dynamic_cast<King*>(choosenPieces[indexOfPiece])
                        ->setCastlingState(
                            !dynamic_cast<King*>(choosenPieces[indexOfPiece])
                                 ->getCastlingState());
                    if (dynamic_cast<King*>(choosenPieces[indexOfPiece])
                            ->getCastlingState())
                        QMessageBox::information(
                            newBoard->view, "Инфо",
                            "Рокировка данной\nфигуре разрешена");
                    else
                        QMessageBox::information(
                            newBoard->view, "Инфо",
                            "Рокировка данной\nфигуре запрещена");
                    return;
                } else if (dynamic_cast<Rook*>(choosenPieces[indexOfPiece])) {
                    dynamic_cast<Rook*>(choosenPieces[indexOfPiece])
                        ->setCastlingState(
                            !dynamic_cast<Rook*>(choosenPieces[indexOfPiece])
                                 ->getCastlingState());
                    if (dynamic_cast<Rook*>(choosenPieces[indexOfPiece])
                            ->getCastlingState())
                        QMessageBox::information(
                            newBoard->view, "Инфо",
                            "Рокировка данной\nфигуре разрешена");
                    else
                        QMessageBox::information(
                            newBoard->view, "Инфо",
                            "Рокировка данной\nфигуре запрещена");
                }
            }
            if (setTakingOnPassage == true) {
                if (dynamic_cast<Pawn*>(choosenPieces[indexOfPiece])) {
                    if ((choosenPieces[indexOfPiece]->isWhite() &&
                         choosenPieces[indexOfPiece]->position.y() ==
                             4 * cellSize) ||
                        (choosenPieces[indexOfPiece]->isBlack() &&
                         choosenPieces[indexOfPiece]->position.y() ==
                             3 * cellSize)) {
                        dynamic_cast<Pawn*>(choosenPieces[indexOfPiece])
                            ->setPassageState(!dynamic_cast<Pawn*>(
                                                   choosenPieces[indexOfPiece])
                                                   ->getPassageState());
                        if (dynamic_cast<Pawn*>(choosenPieces[indexOfPiece])
                                ->getPassageState())
                            QMessageBox::information(
                                newBoard->view, "Инфо",
                                "Взятие данной пешки\nна проходе разрешено");
                        else
                            QMessageBox::information(
                                newBoard->view, "Инфо",
                                "Взятие данной пешки\nна проходе запрещено");
                    }
                }
            }
        });
}
