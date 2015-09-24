#ifndef MEMORYNODE
#define MEMORYNODE

#include <iostream>

/**
 * @file memorynode.h
 * @brief Crea un nodo para ser utilizado por la clase MemoryList
 * @author Juan Pablo Brenes
 * @date 23/9/2015
 */

class MemoryNode{
private:
    unsigned int _fileDescriptor, _amountMem;
    unsigned int _initMem;

    std::string _id;
    MemoryNode *_prev, *_next;
public:
    MemoryNode(); //Constructor sin parametros
    MemoryNode(std::string  pID); //Constructor que recibe el ID
    ~MemoryNode(); //Destructor

    void setPrev(MemoryNode *pPrev); //Método asignar el nodo previo
    MemoryNode *getPrev(); //Método para obtener el nodo previo

    void setNext(MemoryNode *pNext); //Método para asignar el nodo siguiente
    MemoryNode *getNext(); //Método para obtener el nodo siguiente

    bool hasHizq(); //Método que verifica si tiene hijo izquierdo
    bool hasHder(); //Método que verificasi tiene hijo derecho

    unsigned int getFileDescriptor(); //Método para obtener el file descriptor del cliente
    void setFileDescriptor(unsigned int pFD); // Método que asigna el FD al nodo

    unsigned int getInitMem(); //Método para obtener la posición donde inicia la memoria
    void setInitMem(unsigned int pInitMem); //Método que asigna el espacio en memoria del nodo

    unsigned int getAmountMem(); //Método para obtener la cantidad de memoria
    void setAmountMem(unsigned int pAmountMem); //Método que asigna el total de memoria almacenada

    void setID(std::string pID); //Método para asignar el ID del nodo
    std::string getID(); //Método para obtener el ID

};

#endif // MEMORYNODE

