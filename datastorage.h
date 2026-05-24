#ifndef DATASTORAGE_H
#define DATASTORAGE_H

class DataStorage {
   public:
    DataStorage();

    virtual void save() = 0;
    virtual void load() = 0;
};

#endif	// DATASTORAGE_H
