#include "filetxtdatastorage.h"
#include <QDir>
#include <QMessageBox>
#include <QTextStream>

FiletxtDataStorage::FiletxtDataStorage() {}

void FiletxtDataStorage::save() {
    if (startPosition.isEmpty() && !result.isEmpty() && !moves.isEmpty())
        return;
    /*QDir dir("/home/ivan/Документы/453503/ООП/ChessQtOOP/Партии");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    int fileCount = dir.entryList(QStringList("*.txt"), QDir::Files).count();

    QString newFileName =
        QString("/home/ivan/Документы/453503/ОАиП/QtChess/Партии/Партия_%1.txt")
            .arg(fileCount + 1);

    QFile file(newFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл!");
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row <= maxIndexOfRow; row++) {
        QString white =
            notation->item(row, 0) ? notation->item(row, 0)->text() : "";
        QString black =
            notation->item(row, 1) ? notation->item(row, 1)->text() : "";
        out << QString("%1. %2 %3\n").arg(row + 1).arg(white).arg(black);
    }

    out << QString("\nРезультат: %1").arg(result);

    file.close();
    QMessageBox::information(this, "Сохранено",
                             "Партия сохранена в:\n" + newFileName);*/
}
void FiletxtDataStorage::load() {}
