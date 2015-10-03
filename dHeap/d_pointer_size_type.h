#ifndef D_POINTER_SIZE_TYPE_H
#define D_POINTER_SIZE_TYPE_H
#include "dobject.h"
#include <cstdlib>


class d_pointer_size_type
{
private:
    unsigned int ID;
    unsigned int _ptr;
    unsigned int _space;
    unsigned char _type;
    unsigned char _ref;
public:
    d_pointer_size_type();
    int getID()const;
    int getPtr()const;
    int getSpace();
    char getType();
    char getRef();
    void setID(int pID);
    void setPtr(int pPtr);
    void setSpace(int pSpace);
    void setType(char pType);
    void setRef(char pRef);
    bool operator== (const d_pointer_size_type &pPointer);
    void operator= (const d_pointer_size_type &pPointer);
    //incompleto
    void operator= (const dObject &pDObject);
    void operator= (const int pInt);
    /*dObject operator* (const int &p);
    void operator++ (const int p);
    void operator-- (const int p);*/

};

#endif // D_POINTER_SIZE_TYPE_H
