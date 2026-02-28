#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPointF>
#include <QPushButton>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene);
    QTableWidget* notation;
    QPushButton *startButton, *readButton, *exitButton;
    void startWindow();
    void drawScene();

   private:
    Ui::MainWindow* ui;
};
#endif	// MAINWINDOW_H
