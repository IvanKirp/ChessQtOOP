#ifndef FILETXTDATASTORAGE_H
#define FILETXTDATASTORAGE_H
#include "datastorage.h"

class FiletxtDataStorage : public DataStorage {
   public:
    FiletxtDataStorage();

    void save() override;
    void load() override;

    void setDataToSave(DataToSave data) override {
        startPosition = data.startPosition;
        result = data.result;
        moves = data.moves;
    }

   protected:
    QString startPosition = "";
    QString result = "";
    QList<QString> moves{""};
};

#endif	// FILETXTDATASTORAGE_H
