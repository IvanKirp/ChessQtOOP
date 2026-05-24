#ifndef INTERNATIONALNOTATION_H
#define INTERNATIONALNOTATION_H
#include "inotation.h"

class InternationalNotation : public INotation {
   public:
    InternationalNotation();

    QString getChar(QString name) override;
};

#endif	// INTERNATIONALNOTATION_H
