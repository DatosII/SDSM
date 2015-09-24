#include "SDSMMemoryNode/SDSMMemoryNode.h"


/**
 * @brief Constructor del SDSMMemoryNode
 *
 * Recibe los parametros iniciales y convierte el tamaño
 * de memoria que se quiere compartir a bytes
 * Inicializa la lista donde se almacenara toda la información
 * de los clientes y los espacios de memoria que estos almacenan
 *
 * @param pMemory Cantidad de memoria a compartir
 * @param pUnit Unidad de la memoria a compartir (Gigabytes|Megabytes)
 * @param pPort Puerto por el cual se conectaran los clientes
 * @param pStatePort Puerto de estado por el cual se muestra la información de memoria
 */
SDSMMemoryNode::SDSMMemoryNode(const int pMemory, const char pUnit, const int pPort, const int pStatePort){
    _totalMem = (pUnit == 'G')?(pMemory*1024*1024):(pMemory*1024);
    _port = pPort;
    _statePort = pStatePort;
    _initPointer = calloc(1, _totalMem);
    uintptr_t tmp = reinterpret_cast<uintptr_t>(_initPointer);
    _initDirection = (unsigned int)tmp;

    _memoryList = new MemoryList(_initDirection, _totalMem);
}


unsigned char *SDSMMemoryNode::parser(char pBuffer[]){
    char *tmp = strtok(pBuffer, ":");
    std::string method = (std::string)tmp;

    std::string byteStream = (std::string)strtok(NULL, ":");
    unsigned int *_bytes = this->getBytes(byteStream);

    if(method == "d_calloc"){
        return this->d_calloc(this->bytesToInt(_bytes, 0, 3));
    }
    else if (method == "d_free"){}
    else if (method == "d_set"){}
    else if (method == "d_get"){}
    else if (method == "d_status"){}


}


/**
 * @brief Método que crea un arreglo con los bytes enviados al servidor
 *
 * Los bytes de los mensajes llegan en forma hexadecimal y consecutivos,
 * cada byte en hex esta formado por dos caracteres, por lo que se recorre
 * todo el string con los bytes generando sub string con dos caracteres, estos
 * luego se castean a char*, para luego utilizando la función sscanf convertir
 * el char* a un int, que es almacenado en un arreglo.
 *
 * @param pBytes String con los bytes del mensaje
 *
 * @return Arreglo de ints con los bytes
 */
unsigned int* SDSMMemoryNode::getBytes(const std::string pBytes){
    unsigned int _bytes[pBytes.length()/2];

    int posArray = 0;
    for(int i = 0; i < pBytes.length(); i+=2){
        std::string stringByte = pBytes.substr(i, 2);
        char *charByte = (char*)&stringByte[0u];
        unsigned int byte;
        sscanf(charByte, "%x", &byte);
        _bytes[posArray] = byte;
        posArray++;
    }

    return _bytes;
}


/**
 * @brief Método que convierte cuatro bytes a un int
 *
 * @param byteArray Arreglo con los bytes
 * @param pStartIndex Indice dentro del array donde comienzan los bytes
 * @param pEndIndex Indice dentro del array donde terminan los bytes
 *
 * @return Int formado
 *
 */
unsigned int SDSMMemoryNode::bytesToInt(unsigned int* byteArray, const int& pStartIndex, const int& pEndIndex){

    unsigned int newInt = 0;
    int j = 0;
    for(int i = pEndIndex; i >= pStartIndex; --i){
        newInt += (byteArray[i] & 0xFF) << (8*j);
        ++j;
    }

    return  newInt;
}



/**
 * @brief Método que obtiene la representación en bytes de un int
 *
 * @param pInt Número al que quieren obtenerse los bytes
 *
 * @return Puntero a un arreglo con los bytes del numero
 */
unsigned int *SDSMMemoryNode::intToBytes(unsigned int &pInt){
    unsigned int byte0 = pInt >> 24 & 0xFF;
    unsigned int byte1 = pInt >> 16 & 0xFF;
    unsigned int byte2 = pInt >> 8 & 0xFF;
    unsigned int byte3 = pInt & 0xFF;

    unsigned int bytes[] = {byte0, byte1, byte2, byte3};
    return bytes;
}



/**
 * @brief Método que permite a los clientes reservar memoria
 *
 *  Crea un nuevo nodo para la petición del cliente y llama al método
 * de insertar de la lista, el cual debe retornar un arreglo con el resultado
 * de la operacion.
 *
 * Si la primera posicion del arreglo retornado es un 1, significa que no hay
 * espacio para reservar, por lo que retorna el mensaje con un 1.
 *
 * Si la primera posicion del arreglo retornado es 0, significa que si se reservo
 * espacio en la memoria, por lo que se llama al método intToBytes, el cual obtiene
 * la representación en bytes de la direccion de memoria reservada, luego se crea el
 * arreglo de tipo char, con todos los bytes de respuesta que debe enviar el servidor.
 *
 * @param pSize Tamaño en memoria que el cliente desea reservar
 *
 * @return Arreglo de tipo char con los bytes de respuesta
 */
unsigned char *SDSMMemoryNode::d_calloc(unsigned int pSize){
    MemoryNode *newNode = new MemoryNode("ID");
    newNode->setFileDescriptor(1);
    newNode->setAmountMem(pSize);
    unsigned int *result = _memoryList->insert(newNode);

    if(result[0] != 1){
        unsigned int *bytes = this->intToBytes(result[1]);

        unsigned char message[] = {
            (unsigned char)result[0],
            (unsigned char)bytes[0],
            (unsigned char)bytes[1],
            (unsigned char)bytes[2],
            (unsigned char)bytes[3],
        };
        return message;
    }
    else{
        delete newNode;
        unsigned char message[] = {(unsigned char)result[0], 0, 0 ,0, 0};
        return message;
    }
}


/**
 * @brief Método que libera la memoria
 *
 * Libera la memoria especificada por el d_pointer_size, creando un puntero tipo
 * unsigned char que apunta al lugar de memoria del d_pointer_size; con este puntero
 * se eliminan los datos seteando los bytes en 0. Se aumenta el puntero original del
 * nodo en caso que no se quiera borrar todos los bytes asignados.
 *
 * @param pPointer Puntero que indica la ubicación y la cantidad de memoria a eliminar
 *
 * @return
 */
char *SDSMMemoryNode::d_free(d_pointer_size pPointer){
    unsigned char *tmp = (unsigned char*)pPointer._d_pointer._memory;
    for(int i = 0; i<pPointer._bytes; i++){
        *tmp = 0;
        tmp++;
        pPointer._d_pointer._memory+=1;
    }
    //Si el espacio a borrar es igual al espacio total del nodo
    if(pPointer._bytes == pPointer._d_pointer._memory){
        //ELIMINAR EL DATO
    }
}


char *SDSMMemoryNode::d_get(d_pointer_size pPointer){

}


char *SDSMMemoryNode::d_set(d_pointer_size pPointer, std::string pByteStream){

}


char *SDSMMemoryNode::d_status(){

}


