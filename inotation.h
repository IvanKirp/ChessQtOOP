#ifndef INOTATION_H
#define INOTATION_H

#include <QString>
class INotation {
   public:
    INotation();

    virtual QString getChar(QString name) = 0;
};

#endif	// INOTATION_H
