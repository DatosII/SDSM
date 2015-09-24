#ifndef SDSMMEMORYNODE_H
#define SDSMMEMORYNODE_H

#include "Structures/Lists/memorylist.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>



/**
 * @brief d_pointer struct
 *
 * Almacena la ip, y el puerto del SDSMMemoryNode
 * y el lugar donde se encuentra la memoria
 */
struct d_pointer{
    unsigned char _byte0, _byte1, _byte2, _byte3;
    unsigned int _port;
    unsigned int _memory;
};


/**
 * @brief d_pointer_size struct
 *
 * Almacena un d_pointer y un int con la cantidad de bytes
 */
struct d_pointer_size{
    d_pointer _d_pointer;
    unsigned int _bytes;
};


class SDSMMemoryNode{
    
private:
    MemoryList *_memoryList; //Lista que almacena los datos de los clientes
    void* _initPointer; //Puntero donde inicia el espacio de memoria a compartir
    unsigned int _initDirection; //Dirección donde inicia el espacio de memoria a compartir
    unsigned int _totalMem; //Tamaño total en bytes de memoria para compartir
    int _MemUsed; //Cantidad de memoria que se encuentra en uso
    int _port, _statePort; //Puertos

    unsigned int* getBytes(const std::string pBytes); //Método que obtiene los bytes del mensaje
    unsigned  int bytesToInt(unsigned int *byteArray, const int &pStartIndex, const int &pEndIndex); //Método que toma los bytes y los convierte a int
    unsigned int* intToBytes(unsigned int &pInt); //Método que obtiene los bytes de un int
    
public:
    SDSMMemoryNode(const int pMemory, const char pUnit, const int pPort, const int pStatePort);
    unsigned char* parser(char pBuffer[]); //Método que parsea los mensajes entrantes del server
    unsigned char* d_calloc(unsigned int pSize); //Metodo para reservar espacio en memoria
    char* d_free(d_pointer_size pPointer); //Método que libera la memoria
    char* d_get(d_pointer_size pPointer); //Método que obtiene memoria
    char* d_set(d_pointer_size pPointer, std::string pByteStream); //Método que establece memoria
    char* d_status(); //Método que retorna la cantidad de memoria disponible
};

#endif // SDSMMEMORYNODE_H
