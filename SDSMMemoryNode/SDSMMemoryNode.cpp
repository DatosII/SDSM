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
 * @param pUnit Unidad de la memoria a compartir (Gb|Mb)
 * @param pPort Puerto por el cual se conectaran los clientes
 * @param pStatePort Puerto de estado por el cual se muestra la información de memoria
 */
SDSMMemoryNode::SDSMMemoryNode(const int pMemory, const char pUnit, const int pPort, const int pStatePort){
    _totalMem = (pUnit == 'G')?(pMemory*FACTOR*FACTOR):(pMemory*FACTOR);
    _port = pPort;
    _statePort = pStatePort;
    _initPointer = calloc(1, _totalMem);
    uintptr_t tmp = reinterpret_cast<uintptr_t>(_initPointer);
    _initDirection = (unsigned int)tmp;

    _memoryList = new MemoryList(_initDirection, _totalMem);
}



unsigned char *SDSMMemoryNode::parser(unsigned char *pBuffer){

    char *tmp = strtok((char*)pBuffer, SPLIT);
    std::string method = (std::string)tmp;
    std::string byteStream = (std::string)strtok(NULL, SPLIT);
    unsigned char *_bytes = this->getBytes(byteStream);

    if(method == D_CALLOC){
        return this->d_calloc(this->bytesToInt(_bytes, 0, 3)); //SE DEBE HACER DELETE DEL VALOR DE RETORNO
    }
    else if (method == D_FREE){

    }
    else if (method == D_SET){}
    else if (method == D_GET){}
    else if (method == D_STATUS){}
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
unsigned char* SDSMMemoryNode::getBytes(std::string pBytes){
    unsigned char *_bytes = new unsigned char[pBytes.length()/2];

    int posArray = 0;
    for(unsigned int i = 0; i < pBytes.length(); i+=2){
        std::string stringByte = pBytes.substr(i, 2);
        char *charByte = (char*)&stringByte[0u];
        unsigned int byte;
        sscanf(charByte, "%x", &byte);
        _bytes[posArray] = (unsigned char)byte;
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
unsigned int SDSMMemoryNode::bytesToInt(unsigned char* byteArray, const int& pStartIndex, const int& pEndIndex){

    unsigned int newInt = 0;
    int j = 0;
    for(int i = pEndIndex; i >= pStartIndex; --i){
        newInt += (byteArray[i] & 0xFF) << (8*j);
        ++j;
    }

    delete byteArray;
    return  newInt;
}



/**
 * @brief Método que obtiene la representación en bytes de un int
 *
 * @param pInt Número al que quieren obtenerse los bytes
 *
 * @return Puntero a un arreglo con los bytes del numero
 */
unsigned char *SDSMMemoryNode::intToBytes(unsigned int &pInt){
    unsigned char *bytes = new unsigned char[MAX_INDEX];

    for(int index = ZERO, byte = LAST_BYTE; index < MAX_INDEX, byte >= ZERO; index++, byte--){
        bytes[index] = pInt >> (BITS*byte) & 0xFF;
    }
    return bytes;
}



/**
 * @brief Método que convierte dos bytes a unsigned short
 *
 * @param byteArray Arreglo que contiene los bytes
 * @param pStartIndex Indice donde comienzan los bytes
 * @param pEndIndex Indice donde terminan los bytes
 *
 * @return Short formado con los bytes
 */
unsigned short SDSMMemoryNode::bytesToShort(unsigned char *byteArray, const int &pStartIndex, const int &pEndIndex){

    return (unsigned short) (((byteArray[pStartIndex] << 8)) | ((byteArray[pEndIndex] & 0xff)));
}


/**
 * @brief Método que convierte un short a su representación en bytes
 *
 * @param pShort Short al que quieren obtenerse los bytes
 *
 * @return Arreglo con los bytes
 */
unsigned char *SDSMMemoryNode::shortToBytes(unsigned short pShort){
    unsigned char bytes[1];

    bytes[0] = (pShort & 0xFF00) >> 8;
    bytes[1] = pShort & 0x00FF;

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

    std::cout << "ENTRE " << "\n"; //"#######################################################"

    MemoryNode *newNode = new MemoryNode("ID");
    newNode->setFileDescriptor(1);
    newNode->setAmountMem(pSize);
    unsigned int *result = _memoryList->insert(newNode);

    unsigned char *message = new unsigned char[5];


   // if(result[0] == 1) delete newNode;

    std::cout << result[1] << "\n";
    unsigned char *bytes = this->intToBytes(result[1]);

    message[0] = (unsigned char)result[0];
    for(int i=0; i<(sizeof(bytes)); i++){
        message[i+1] = bytes[i];
    }

    delete result;
    delete bytes;
    return message;


//    if(result[0] != 1){
//        unsigned char *bytes = this->intToBytes(result[1]);

//        message[0] = (unsigned char)result[0];
//        for(int i=0; i<(sizeof(bytes)/2); i++){
//            message[i+1] = bytes[i];
//        }

//        delete result;
//        return message;
//    }
//    else{
//        delete newNode;
//         message[0] = (unsigned)
//         {(unsigned char)result[0], 0, 0 ,0, 0};
//        return message;
//    }
}



/**
 * @brief Método que libera la memoria
 *
 * Se busca en la lista si el cliente que solicita la liberacion de memoria, tiene
 * reservado el espacio que desea liberar.
 * Si valor de retorno de la busqueda del nodo
 * es diferente de NULL, significa que se encontro el nodo, por lo que se libera la memoria,
 * luego se comprueba si la cantidad de bytes a liberar es igual a la cantidad de memoria
 * reservada, si lo es significa que se debe borrar el nodo.
 *
 * @param pPointer Puntero que indica la ubicación y la cantidad de memoria a eliminar
 *
 * @return Char con un 0 si se la operacion se realizo correctamente,
 *         un 2 si se intento acceder a un espacio de memoria no permitido o si la
 *         ocurrio algun error durante el método
 */
unsigned char SDSMMemoryNode::d_free(d_pointer_size pPointer){
    MemoryNode *node = _memoryList->find("ID", pPointer._d_pointer._memory);

    //La memoria a liberar a sido reservada previamente por el mismo cliente
    if(node != NULL){
        unsigned char *tmp = (unsigned char*)pPointer._d_pointer._memory;
        for(int i = 0; i<pPointer._bytes; i++){// Se recorre la memoria borrando los bytes
            *tmp = 0;
            tmp++;
            node->setInitMem(node->getInitMem()+1);
        }
        //Si el espacio a borrar es igual al total de memoria reservada, se elimina el nodo
        if(node->getAmountMem() == pPointer._bytes){
            _memoryList->remove(node);
        }
        unsigned char message = 0;
        return message;
    }

    //La memoria no a sido reservada o pertenece a otro cliente
    else{
        unsigned char message = 2;
        return message;
    }









}



char *SDSMMemoryNode::d_get(d_pointer_size pPointer){

}



char *SDSMMemoryNode::d_set(d_pointer_size pPointer, std::string pByteStream){

}



char *SDSMMemoryNode::d_status(){

}


