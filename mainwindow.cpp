#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->QAbstractButton::move(400, 100);
    setFixedSize(1100, 800);
    setWindowTitle("Chess");
    notation->hide();
    startWindow();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startWindow() {
    setStyleSheet(
        "QMainWindow { border-image: "
        "url(:/images/start_window.png) 0 0 0 0 stretch stretch;}");
    setWindowTitle("Chess");

    startButton = new QPushButton(this);
    startButton->setGeometry(400, 225, 300, 100);
    startButton->setText("Новая игра");
    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: transparent;"
        "border: 2px solid black;"
        "font: bold 50px 'Arial';"
        "color: rgb(0, 0, 0);}"
        "QPushButton:hover {"
        "   background-color: green;"
        "   color: rgb(234, 255, 3);}");
    startButton->show();

    readButton = new QPushButton(this);
    readButton->setGeometry(400, 350, 300, 100);
    readButton->setText("Загрузить\nиз файла");
    readButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: 2px solid black;"
        "font: bold 40px 'Arial';"
        "   color: rgb(0, 0, 0);}"
        "QPushButton:hover {"
        "   background-color: green;"
        "   color: rgb(234, 255, 3);}");
    readButton->show();

    exitButton = new QPushButton(this);
    exitButton->setGeometry(400, 475, 300, 100);
    exitButton->setText("Выход");
    exitButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: 2px solid black;"
        "font: bold 50px 'Arial';"
        "   color: rgb(0, 0, 0);}"
        "QPushButton:hover {"
        "   background-color: green;"
        "   color: rgb(234, 255, 3);}");
    exitButton->show();


    connect(startButton, &QPushButton::clicked, this,
            &MainWindow::chooseGameMode);
    //connect(readButton, &QPushButton::clicked, this, &MainWindow::getFromFile);
    connect(exitButton, &QPushButton::clicked, [this] { this->close(); });
}

void MainWindow::chooseGameMode() {
    setStyleSheet(
        "QMainWindow { border-image: "
        "url(:/images/choose_gamemode.png) 0 0 0 0 stretch stretch;}");

    startButton->hide();
    readButton->hide();
    exitButton->hide();

    QPushButton* classicButton = new QPushButton("Классические шахматы", this);
    allGameModeButtons.append(classicButton);
    connect(classicButton, &QPushButton::clicked, [this]() {
        ClassicGame* gamemode = new ClassicGame(newBoard);
        drawScene(gamemode);
    });

    QPushButton* fischerButton = new QPushButton("Шахматы Фишера", this);
    allGameModeButtons.append(fischerButton);
    connect(fischerButton, &QPushButton::clicked, [this]() {
        bool ok;
        int number = QInputDialog::getInt(
            this, "Позиция", "Введите номер позиции", 1, 1, 960, 1, &ok);
        if (ok) {
            FischerChess* gamemode = new FischerChess(newBoard, number);
            drawScene(gamemode);
        }
    });

    QPushButton* antiChessButton = new QPushButton("Поддавки", this);
    allGameModeButtons.append(antiChessButton);
    connect(antiChessButton, &QPushButton::clicked, [this]() {
        AntiChess* gamemode = new AntiChess(newBoard);
        drawScene(gamemode);
    });

    QPushButton* threeChecksButton = new QPushButton("Три шаха", this);
    allGameModeButtons.append(threeChecksButton);
    connect(threeChecksButton, &QPushButton::clicked, [this]() {
        ThreeChecks* gamemode = new ThreeChecks(newBoard);
        drawScene(gamemode);
    });

    QPushButton* customButton = new QPushButton("Расставить позицию", this);
    allGameModeButtons.append(customButton);
    connect(customButton, &QPushButton::clicked, [this]() {
        //QList<QPushButton*> choosePieceButtons;
        for (int i = 0; i < 12; i++) {
            choosePieceButtons.append(new QPushButton(this));
            if (i < 6)
                choosePieceButtons[i]->setGeometry(
                    8 * cellSize + 10, i * cellSize, cellSize, cellSize);
            else if (i >= 6)
                choosePieceButtons[i]->setGeometry(
                    9 * cellSize + 10, (11 - i) * cellSize, cellSize, cellSize);
        }

        QPushButton* deleteButton = new QPushButton("Удалить фигуру", this);
        choosePieceButtons.append(deleteButton);
        deleteButton->setGeometry(8 * cellSize + 10, 6 * cellSize, 2 * cellSize,
                                  cellSize / 2);
        QPushButton* startButton =
            new QPushButton("Продолжить с этой позиции", this);
        choosePieceButtons.append(startButton);
        startButton->setGeometry(8 * cellSize + 10, 7 * cellSize + cellSize / 2,
                                 2 * cellSize, cellSize / 2);

        QPushButton* setCastling = new QPushButton(
            "Разрешить/запретить\nкоролю/ладье рокировку", this);
        choosePieceButtons.append(setCastling);
        setCastling->setGeometry(8 * cellSize + 10, 6 * cellSize + cellSize / 2,
                                 2 * cellSize, cellSize / 2);

        QPushButton* setPassage =
            new QPushButton("Разрешить/запретить\nвзятие на проходе", this);
        choosePieceButtons.append(setPassage);
        setPassage->setGeometry(8 * cellSize + 10, 7 * cellSize, 2 * cellSize,
                                cellSize / 2);

        CustomSetupMode* gamemode =
            new CustomSetupMode(newBoard, choosePieceButtons);
        drawScene(gamemode);
        choosePieceButtons.clear();
    });

    for (int i = 0; i < allGameModeButtons.size(); i++) {
        allGameModeButtons[i]->setGeometry(250, 100 * i + 25, 600, 80);
        allGameModeButtons[i]->setStyleSheet(
            "QPushButton {"
            "background-color: transparent;"
            "border: 4px solid black;"
            "font: bold 50px 'Arial';"
            "color: rgb(255, 0, 0);}"
            "QPushButton:hover {"
            "   background-color: green;"
            "   color: rgb(234, 255, 3);}");
        allGameModeButtons[i]->show();
    }
}

void MainWindow::drawScene(GameMode* gamemode) {
    ColorObserver* colorObserver = new ColorObserver();
    auto newColor = [this, gamemode, colorObserver]() {
        int number = gamemode->counterOfMoves;
        QList<QPushButton*> buttons = gamemode->allChessPieceButtons;
        QList<QString> colors;
        for (int i = 0; i < buttons.size(); i++) {
            colors.append(gamemode->allChessPieces[i]->getColor());
        }
        bool isGameOver = gamemode->isGameOver;
        colorObserver->setNewColor(buttons, colors, number, isGameOver);
    };
    connect(gamemode, &GameMode::moveIsMade, this, newColor);
    connect(gamemode, &GameMode::startGame, this, newColor);

    connect(gamemode, &GameMode::home, [this, gamemode] {
        for (int i = 0; i < gamemode->allChessPieceButtons.size(); i++) {
            newBoard->deleteFromChessboard(gamemode->allChessPieceButtons[i]);
        }
        gamemode->clearAllLists();
        MouseEventMediator::getInstance()->clearGamemode();
        gamemode->deleteLater();
        view->hide();
        notation->hide();
        startWindow();
    });

    //выбор языка шахматной нотации
    InternationalNotation* lang = new InternationalNotation();
    ChessNotation* chessNotation = new ChessNotation(notation, lang);
    gamemode->setChessNotation(chessNotation);

    //выбор варианта сохранения/загрузки
    FiletxtDataStorage* filetxtDataStorage = new FiletxtDataStorage();
    gamemode->setDataStorage(filetxtDataStorage);

    for (int i = 0; i < allGameModeButtons.size(); i++) {
        delete allGameModeButtons[i];
        allGameModeButtons[i] = nullptr;
    }
    allGameModeButtons.clear();
    setStyleSheet(
        "QMainWindow { border-image: "
        "url(:/images/next_window.png) 0 0 0 0 stretch stretch;}");
    setWindowTitle("Chess");

    view->setScene(myScene);
    newBoard->scene = myScene;
    setCentralWidget(view);
    myScene->drawScene();

    gamemode->ChessPieceManager();
}
