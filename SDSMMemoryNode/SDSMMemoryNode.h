#ifndef SDSMMEMORYNODE_H
#define SDSMMEMORYNODE_H

#include "Structures/Lists/memorylist.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <mutex>


#define FACTOR 1024
#define ZERO 0
#define LAST_BYTE 3
#define MAX_INDEX 4
#define BITS 8
#define DEFAULT_MEM 500
#define BYTE_STREAM_OFFSET 14
#define HEX_LEN 2
#define HEX_255 0xff
#define NEW_LINE "\n"
#define HEX_FORMAT "%x"
#define GB 'G'
#define MB 'M'
#define SPLIT ":"
#define SPLIT_IP "."
#define D_CALLOC "d_calloc"
#define D_FREE "d_free"
#define D_SET "d_set"
#define D_GET "d_get"
#define D_STATUS "d_status"
#define UNKNOW_UNIT "POR FAVOR INGRESE UNA UNIDAD CORRECTA <G|M>"
#define DEFAULT_MEMORY "SE RESERVO POR DEFECTO 500 BYTES"



/**
 * @brief d_pointer struct
 *
 * Almacena la ip, y el puerto del SDSMMemoryNode
 * y el lugar donde se encuentra la memoria
 */
struct d_pointer{
	unsigned char _ip[4];
	unsigned short _port;
	unsigned int _memDirection;
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
    
public:
	std::mutex _mutex;
	std::string _ip;
	unsigned char _ipBytes[4];
    MemoryList *_memoryList; //Lista que almacena los datos de los clientes
    void* _initPointer; //Puntero donde inicia el espacio de memoria a compartir
    unsigned int _initDirection; //Dirección donde inicia el espacio de memoria a compartir
    unsigned int _totalMem; //Tamaño total en bytes de memoria para compartir
	unsigned int _memUsed; //Cantidad de memoria que se encuentra en uso
	short _port; //Puerto cliente
	short _statePort; //Puerto de estado

	unsigned char *getBytes(std::string pBytes); //Método que obtiene los bytes del mensaje
	unsigned  int bytesToInt(unsigned char *byteArray, const int &pStartIndex, const int &pEndIndex); //Método que toma los bytes y los convierte a int
	unsigned char *intToBytes(unsigned int &pInt); //Método que obtiene los bytes de un int
	unsigned short bytesToShort(unsigned char *byteArray, const int &pStartIndex, const int &pEndIndex); //Método que toma los bytes y losconvierte a short
	unsigned char* shortToBytes(unsigned short pShort); //Método que obtiene los bytes de un short
	d_pointer_size* setUpPointer(unsigned char  *pByteArray);

	void getIP(unsigned char *pArray); //LLena el array con la dirección ip de la computadora
	unsigned int getRealAddress(unsigned int pVirtualAddress); //Método que obtiene la dirreción real en memoria

    
public:
	SDSMMemoryNode(const unsigned int pMemory, const char pUnit, const std::string pIP, const unsigned short pPort, const unsigned short pStatePort);
	unsigned char* parser(unsigned char *pBuffer); //Método que parsea los mensajes entrantes del server
    unsigned char* d_calloc(unsigned int pSize); //Metodo para reservar espacio en memoria
	unsigned char d_free(d_pointer_size *pPointer); //Método que libera la memoria
	unsigned char* d_get(d_pointer_size *pPointer); //Método que obtiene memoria
	unsigned char d_set(d_pointer_size *pPointer, unsigned char *pByteStream); //Método que establece memoria
	unsigned char* d_status(); //Método que retorna la cantidad de memoria disponible
};

#endif // SDSMMEMORYNODE_H
