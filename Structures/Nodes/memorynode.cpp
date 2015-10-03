#include "Structures/Nodes/memorynode.h"



/**
 * @brief Constructo sin parametros
 *
 * Inicializa todos los atributos en 0
 */
MemoryNode::MemoryNode(){
    _prev = 0;
    _next = 0;
    _fileDescriptor = 0;
    _amountMem = 0;
    _initMem = 0;
    _id = "";

}


/**
 * @brief Constructor que recibe el ID
 *
 * Inicializa los demás atributos en 0;
 *
 * @param pID ID del nodo(ID cliente)
 */
MemoryNode::MemoryNode(std::string pID){
    _prev = 0;
    _next = 0;
    _fileDescriptor = 0;
    _amountMem = 0;
    _initMem = 0;
    _id = pID;
}


/**
 * @brief Método para asignar el nodo anterior
 *
 * @param pPrev Nodo anterior
 */
void MemoryNode::setPrev(MemoryNode *pPrev){
    _prev = pPrev;
}


/**
 * @brief Método que obtiene el nodo anterior
 *
 * @return Nodo anterior
 */
MemoryNode *MemoryNode::getPrev(){
    return _prev;
}


/**
 * @brief Método para asignar el nodo siguiente
 *
 * @param pNext Nodo siguiente
 */
void MemoryNode::setNext(MemoryNode *pNext){
    _next = pNext;
}


/**
 * @brief Método que obtiene el nodo siguiente
 *
 * @return Nodo siguiente
 */
MemoryNode *MemoryNode::getNext(){
    return _next;
}


/**
 * @brief Método que obtiene el File Descriptor del cliente
 *
 * @return File Descriptor
 */
unsigned int MemoryNode::getFileDescriptor(){
    return _fileDescriptor;
}


/**
 * @brief Método para asignar el File Descriptor
 *
 * @param pFD File Descriptor
 */
void MemoryNode::setFileDescriptor(unsigned int pFD){
    _fileDescriptor = pFD;
}


/**
 * @brief Método que obtiene la dirección de memoria donde se almacena el o los datos
 *
 * @return Dirección del espacio en memoria que puede utilizar el cliente
 */
unsigned int MemoryNode::getMemAddress(){
    return _initMem;
}


/**
 * @brief Método que asigna la dirección de memoria del espacio que el cliente puede utilizar
 *
 * @param pInitMem Dirección del espacio en memoria que puede utilizar el cliente
 */
void MemoryNode::setMemAddress(unsigned int pInitMem){
    _initMem = pInitMem;
}


/**
 * @brief Método que retorna la cantidad de memoria que el cliente tiene reservada
 *
 * @return Cantidad de memoria que el cliente tiene reservada
 */
unsigned int MemoryNode::getAmountMem(){
    return _amountMem;
}


/**
 * @brief Método para asignar la cantidad de memoria que el cliente desea reservar
 *
 * @param pAmountMem Cantidad de memoria a reservar (bytes)
 */
void MemoryNode::setAmountMem(unsigned int pAmountMem){
    _amountMem = pAmountMem;
}


/**
 * @brief Método para asignar el ID del cliente al nodo
 *
 * @param pID ID del cliente
 */
void MemoryNode::setID(std::string pID){
    _id = pID;
}


/**
 * @brief Método para obtener el ID del cliente
 *
 * @return ID del cliente
 */
std::string MemoryNode::getID(){
    return _id;
}


/**
 * @brief Destructor de la clase
 *
 * Asigna 0 (NULL) a los punteros al nodo anterior y siguiente
 */
MemoryNode::~MemoryNode(){
	_prev = 0;
	_next = 0;
}




































