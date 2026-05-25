#ifndef FILETXTDATASTORAGE_H
#define FILETXTDATASTORAGE_H
#include "datastorage.h"

class FiletxtDataStorage : public DataStorage {
   public:
    FiletxtDataStorage();

    void save() override;
    void load() override;

    void setDataToSave(GameData data) override {
        nameOfMode = data.nameOfMode;
        startPosition = data.startPosition;
        result = data.result;
        moves = data.moves;
    }

    GameData getDataFromLoad() override {
        GameData data;
        data.nameOfMode = nameOfMode;
        data.startPosition = startPosition;
        data.result = result;
        data.moves = moves;
        return data;
    }

   protected:
    QString nameOfMode;
    QString startPosition = "";
    QString result = "";
    QList<QString> moves{""};
};

#endif	// FILETXTDATASTORAGE_H
