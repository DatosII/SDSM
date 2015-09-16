#ifndef SDSMMEMORYNODE_H
#define SDSMMEMORYNODE_H

struct d_pointer_size{
    
};

class SDSMMemoryNode{
    

    
private:
    int* _direction;
    int _totalSize;
    
public:
    unsigned char* d_calloc(int pSize); //Metodo para reservar espacio en memoria
    //int d_free()

    
    
};

#endif // SDSMMEMORYNODE_H
