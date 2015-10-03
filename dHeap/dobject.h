#ifndef DOBJECT_H
#define DOBJECT_H

#include <iostream>

class dObject {
private:
    std::string dObjectType;
    void* dObjectPuntData;
public:
    dObject();
    std::string getDObjectType();
    void setDObjectType(std::string pType);
    void* getDObjectPuntData();
    void setDObjectPuntData(void *pPuntData);   
};
#endif // DOBJECT_H
