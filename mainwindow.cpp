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
    //connect(exitButton, &QPushButton::clicked, this, &MainWindow::exit);
}

void MainWindow::chooseGameMode() {
    delete startButton;
    startButton = nullptr;
    delete readButton;
    readButton = nullptr;
    delete exitButton;
    exitButton = nullptr;

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
    for (int i = 0; i < allGameModeButtons.size(); i++) {
        delete allGameModeButtons[i];
        allGameModeButtons[i] = nullptr;
    }
    allGameModeButtons.clear();
    setStyleSheet(
        "QMainWindow { border-image: "
        "url(:/images/next_window.png) 0 0 0 0 stretch stretch;}");
    setWindowTitle("Chess");
    notation = new QTableWidget(this);

    GameScene* myScene = new GameScene(scene, view, newBoard, notation);
    view->setScene(myScene);
    newBoard->scene = myScene;
    setCentralWidget(view);
    myScene->drawScene();

    /*
    Scene* myScene = new Scene(scene, view, newBoard, notation);
    view->setScene(myScene);

    newBoard->scene = myScene;

    setCentralWidget(view);
    myScene->drawScene();*/

    //ClassicGame* game = new ClassicGame(newBoard, allChessPieceButtons);
    //FischerChess* game = new FischerChess(newBoard, allChessPieceButtons, 480);
    gamemode->ChessPieceManager();
}
