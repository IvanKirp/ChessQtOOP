#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QList>
#include <QString>


struct DataToSave {
    QString startPosition;
    QString result;
    QList<QString> moves;
};

class DataStorage {
   public:
    DataStorage();

    virtual void save() = 0;
    virtual void load() = 0;
    virtual void setDataToSave(DataToSave data) = 0;
};

#endif	// DATASTORAGE_H
