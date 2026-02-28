#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "bishop.h"
#include "chessboard.h"
#include "chesspiece.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "qeuen.h"
#include "rook.h"
#include "scene.h"

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
    this->QAbstractButton::move(400, 100);

    setFixedSize(1100, 800);
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


    connect(startButton, &QPushButton::clicked, this, &MainWindow::drawScene);
    //connect(readButton, &QPushButton::clicked, this, &MainWindow::getFromFile);
    //connect(exitButton, &QPushButton::clicked, this, &MainWindow::exit);
}

void MainWindow::drawScene() {
    delete startButton;
    startButton = nullptr;
    delete readButton;
    readButton = nullptr;
    delete exitButton;
    exitButton = nullptr;

    setStyleSheet(
        "QMainWindow { border-image: "
        "url(:/images/next_window.png) 0 0 0 0 stretch stretch;}");

    notation = new QTableWidget(this);
    setCentralWidget(view);
    Scene* myScene = new Scene();
    myScene->drawScene(scene, view, notation);
}
