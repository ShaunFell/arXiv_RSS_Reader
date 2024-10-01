#ifndef READERFACTORY_H_INCLUDED
#define READERFACTORY_H_INCLUDED

#include <QString>
#include "Reader.h"



class ReaderFactory
{

public:
    Reader* new_reader(QString url) const 
    {
        Reader* reader_ptr = new Reader(url);
        return reader_ptr;
    }

}




#endif