#ifndef FILETXTDATASTORAGE_H
#define FILETXTDATASTORAGE_H
#include "datastorage.h"

class FiletxtDataStorage : public DataStorage {
   public:
    FiletxtDataStorage();

    void save() override;
    void load() override;
};

#endif	// FILETXTDATASTORAGE_H
