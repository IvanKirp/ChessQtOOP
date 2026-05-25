#include "filetxtdatastorage.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextStream>

FiletxtDataStorage::FiletxtDataStorage() {}

void FiletxtDataStorage::save() {
    if (startPosition.isEmpty() && !result.isEmpty() && !moves.isEmpty())
        return;
    QDir dir("/home/ivan/Документы/453503/ООП/ChessQtOOP/Партии");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    int fileCount = dir.entryList(QStringList("*.txt"), QDir::Files).count();

    QString newFileName =
        QString(
            "/home/ivan/Документы/453503/ООП/ChessQtOOP/Партии/Партия_%1.txt")
            .arg(fileCount + 1);

    QFile file(newFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Ошибка Не удалось создать файл!";
        return;
    }

    QTextStream out(&file);
    out << QString("startPosition: %1\n").arg(startPosition);
    out << QString("Режим игры: %1\n").arg(nameOfMode);

    for (int i = 0; i < moves.size() / 2; i++) {
        out << QString("%1. %2 %3\n")
                   .arg(i + 1)
                   .arg(moves[2 * i])
                   .arg(moves[2 * i + 1]);
    }

    out << QString("\nРезультат: %1").arg(result);

    file.close();
}

void FiletxtDataStorage::load() {
    // Открываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,  // parent (можно передать указатель на MainWindow, если есть)
        "Выберите файл с партией",
        "/home/ivan/Документы/453503/ООП/ChessQtOOP/Партии",
        "Текстовые файлы (*.txt)");

    // Если пользователь отменил выбор
    if (filePath.isEmpty()) {
        qDebug() << "Выбор файла отменён";
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка: Не удалось открыть файл!" << filePath;
    }

    QTextStream in(&file);
    moves.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.isEmpty()) {
            continue;  // Пропускаем пустые строки
        }

        // Парсим startPosition
        if (line.startsWith("startPosition:")) {
            startPosition =
                line.mid(QString("startPosition:").length()).trimmed();
        }
        // Парсим режим игры
        else if (line.startsWith("Режим игры:")) {
            nameOfMode = line.mid(QString("Режим игры:").length()).trimmed();
        }
        // Парсим результат
        else if (line.startsWith("Результат:")) {
            result = line.mid(QString("Результат:").length()).trimmed();
        }
        // Парсим ходы (строки вида "1. e2-e4 e7-e5")
        else if (line.contains(QRegularExpression("^\\d+\\."))) {
            // Разделяем строку на части
            QStringList parts = line.split(QRegularExpression("\\s+"));

            if (parts.size() >= 2) {
                moves.append(parts[1]);	 // Добавляем ход белых
            }
            if (parts.size() >= 3) {
                moves.append(parts[2]);	 // Добавляем ход чёрных
            }
        }
    }

    file.close();
}
