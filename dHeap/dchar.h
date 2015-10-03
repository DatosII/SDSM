#ifndef DCHAR_H
#define DCHAR_H
#include "d_pointer_size_type.h"

#include <iostream>

class dChar:public d_pointer_size_type{
private:
    char dCharData;
public:
    dChar();
    ~dChar();
};

#endif // DCHAR_H
