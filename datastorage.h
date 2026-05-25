#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QList>
#include <QString>


struct GameData {
    QString nameOfMode;
    QString startPosition;
    QString result;
    QList<QString> moves;
};

class DataStorage {
   public:
    DataStorage();

    virtual void save() = 0;
    virtual void load() = 0;
    virtual void setDataToSave(GameData data) = 0;
    virtual GameData getDataFromLoad() = 0;
};

#endif	// DATASTORAGE_H
