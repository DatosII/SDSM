#include "d_pointer_size_type.h"

d_pointer_size_type::d_pointer_size_type(){
    this->_ptr=5;
}

int d_pointer_size_type::getID()const{
    return ID;
}

int d_pointer_size_type::getPtr()const{
    return _ptr;
}

int d_pointer_size_type::getSpace(){
    return _space;
}

char d_pointer_size_type::getType(){
    return _type;
}

char d_pointer_size_type::getRef(){
    return _ref;
}

void d_pointer_size_type::setID(int pID){
    this->ID=pID;
}

void d_pointer_size_type::setPtr(int pPtr){
    this->_ptr=pPtr;
}

void d_pointer_size_type::setSpace(int pSpace){
    this->_space=pSpace;
}

void d_pointer_size_type::setType(char pType){
    this->_type=pType;
}

void d_pointer_size_type::setRef(char pRef){
    this->_ref= static_cast<unsigned int>(this->_ref) + static_cast<unsigned int>(pRef);
}

bool d_pointer_size_type::operator== (const d_pointer_size_type &pPointer){
    return (pPointer.getPtr() == this->getPtr());
}

void d_pointer_size_type::operator= (const d_pointer_size_type &pPointer){
    this->setID(pPointer.getID());
    return;
}

void d_pointer_size_type::operator =(const  dObject &pDObject){
    return;
}

void  d_pointer_size_type::operator =(const int pInt){
    return ;
}
