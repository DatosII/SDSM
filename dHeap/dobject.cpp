#include "dobject.h"

dObject::dObject(){
}

std::string dObject::getDObjectType(){
    return dObjectType;
}

void dObject::setDObjectType(std::string pType){
    this->dObjectType=pType;
}

void* dObject::getDObjectPuntData(){
    return dObjectPuntData;
}

void dObject::setDObjectPuntData(void *pPuntData){
    this->dObjectPuntData= pPuntData;
}
