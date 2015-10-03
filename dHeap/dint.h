#ifndef DINT_H
#define DINT_H
#include "d_pointer_size_type.h"
#include <iostream>

class dInt:public d_pointer_size_type{
private:
    int dIntData;

public:
    dInt();
    ~dInt();

/*
    void* operator new(size_t psize, void* pdObject){
        return pdObject;
    }
*/
};

#endif // DINT_H
