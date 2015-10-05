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
SDSMMemoryNode::SDSMMemoryNode(const unsigned int pMemory, const char pUnit, const std::string pIP,
							   const unsigned short pPort, const unsigned short pStatePort){

	if(pUnit == GB) _totalMem = (pMemory*FACTOR*FACTOR*FACTOR);

	else if (pUnit == MB) _totalMem = (pMemory*FACTOR*FACTOR);

	else {
		_totalMem = DEFAULT_MEM;
		std::cout << UNKNOW_UNIT << NEW_LINE;  std::cout << DEFAULT_MEMORY << NEW_LINE;
	}

	this->_ip = pIP;
	this->getIP(_ipBytes);
	this->_port = pPort;
	this->_statePort = pStatePort;
	this->_memUsed = 0;
	this->_initPointer = calloc(1, _totalMem);
	uintptr_t tmp = reinterpret_cast<uintptr_t>(_initPointer);
	this->_initDirection = (unsigned int)tmp;
	this->_memoryList = new MemoryList(_initDirection, _totalMem);
}



/**
 * @brief Método que recibe el buffer de bytes del server
 *
 * Recibe el buffer de bytes del server y obtiene los parametros para ejecutar
 * los métodos d_calloc, d_get, d_set, d_free, d_status.
 *
 * @param pBuffer Buffer de bytes del server
 *
 * @return Mensaje de respuesta al cliente
 */
unsigned char *SDSMMemoryNode::parser(unsigned char *pBuffer){

	//char *tmp = strtok((char*)pBuffer, SPLIT);
	//std::string method = (std::string)tmp;
	//std::string stringBytes = (std::string)strtok(NULL, SPLIT);
	std::string method = this->getMethod(pBuffer);
	std::string stringBytes = this->getByteStream(pBuffer);
	unsigned char *_bytes = this->getBytes(stringBytes);

    if(method == D_CALLOC){
		unsigned int *amountMem = (unsigned int*)_bytes;
		unsigned char *status = this->d_calloc(*amountMem); //SE DEBE HACER DELETE DEL VALOR DE RETORNO
		delete _bytes;
		std::cout << "FUNCIONA!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
		return  status;
    }
	else if (method == D_FREE){
		d_pointer_size *pointer = this->setUpPointer(_bytes);
		unsigned char status = this->d_free(pointer);
		delete pointer;
		return (unsigned char*)&status;
    }
	else if (method == D_SET){
		d_pointer_size *pointer = this->setUpPointer(_bytes);
		unsigned char *byteStream = _bytes+BYTE_STREAM_OFFSET;
		unsigned char status = this->d_set(pointer, byteStream);
		delete pointer;
		return (unsigned char*)&status;
	}
	else if (method == D_GET){
		d_pointer_size *pointer = this->setUpPointer(_bytes);
		unsigned char *byteStream = this->d_get(pointer); //SE DEBE HACER DELETE DEL VALOR DE RETORNO
		delete pointer;
		return byteStream;
	}
	else if (method == D_STATUS){
		return this->d_status();
	}
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

	//Se crea el nodo que almacena la informacion del cliente
    MemoryNode *newNode = new MemoryNode("ID");
    newNode->setFileDescriptor(1);
    newNode->setAmountMem(pSize);

	_mutex.lock();
    unsigned int *result = _memoryList->insert(newNode);
	_mutex.unlock();

	unsigned char *message = new unsigned char[11];

    if(result[0] == 1) delete newNode;
	else _memUsed+=pSize;

	unsigned char *memBytes = this->intToBytes(result[1]);
	unsigned char *portBytes = this->shortToBytes(_port);

    message[0] = (unsigned char)result[0];
	for(int i = 0; i < (sizeof(_ipBytes)); i++){
		message[i+1] = _ipBytes[i];
	}

	message[5] = portBytes[0];
	message[6] = portBytes[1];

	for(int i=0; i<(sizeof(memBytes)); i++){
		message[i+7] = memBytes[i];
    }

    delete result;
	delete memBytes;
	delete portBytes;

    return message;
}



/**
 * @brief Método que libera la memoria
 *
 * Se obtiene la dirección real del espacio reservado en memoria, sumando la dirección
 * virtual enviada con la dirección real del inicio del espacio de reserva.
 *
 * Se busca en la lista si el cliente que solicita la liberacion de memoria, tiene
 * reservado el espacio que desea liberar.
 *
 * Si valor de retorno de la busqueda del nodo es diferente de NULL, significa que
 * se encontro el nodo, por lo que se libera la memoria, luego se comprueba si la
 * cantidad de bytes a liberar es igual a la cantidad de memoria reservada, si lo
 * es significa que se debe borrar el nodo.
 *
 * @param pPointer Puntero que indica la ubicación y la cantidad de memoria a eliminar
 *
 * @return Char con un 0 si se la operacion se realizo correctamente,
 *         un 1 si se intento acceder a un espacio de memoria no reservado
 */
unsigned char SDSMMemoryNode::d_free(d_pointer_size *pPointer){
	unsigned int realDirection = this->getRealAddress(pPointer->_d_pointer._memDirection);
	_mutex.lock();
	MemoryNode *node = _memoryList->find("ID", pPointer->_d_pointer._memDirection);
	_mutex.unlock();
	unsigned char message;

    //La memoria a liberar a sido reservada previamente por el mismo cliente
	if(node != NULL){
		if(pPointer->_bytes <= node->getAmountMem()){
			unsigned char *tmp = (unsigned char*)realDirection;
			for(int i = 0; i<pPointer->_bytes; i++){// Se recorre la memoria borrando los bytes
				*tmp = 0;
				tmp++;
				node->setMemAddress(node->getMemAddress()+1);
			}
			_memUsed-=pPointer->_bytes;
			//Si el espacio a borrar es igual al total de memoria reservada, se elimina el nodo
			if(node->getAmountMem() == pPointer->_bytes){
				_mutex.lock();
				_memoryList->remove(node);
				_mutex.unlock();
			}
			message = 0;
			return message;
		}
		else{
			message = 1;
			return message;
		}
	}

    //La memoria no a sido reservada o pertenece a otro cliente
    else{
		message = 1;
        return message;
    }
}



/**
 * @brief Método que guarda los bytes en la memoria previamente reservada
 *
 * Se obtiene la dirección real del espacio reservado en memoria, sumando la dirección
 * virtual enviada con la dirección real del inicio del espacio de reserva.
 *
 * Se busca en la lista si el cliente que solicita la operación a reservado previamente
 * la memoria en la dirección obtenida.
 *
 * Si la  memoria se reservo previamente y la cantidad de bytes a almacenar es menor o
 * igual a la cantidad de bytes reservados, se recorre la memoria almacenando los bytes
 * del byteStream.
 *
 * @param pPointer Struct tipo d_pointer_size con los parametros
 * @param pByteStream Arreglo tipo unsigned char con los bytes a almacenar
 *
 * @return Char con un 0 si se la operacion se realizo correctamente,
 *         un 1 si la memoria no se habia reservado anteriormente o si
 *		   intenta accerder a memoria no reservada
 */
unsigned char SDSMMemoryNode::d_set(d_pointer_size *pPointer, unsigned char *pByteStream){
	unsigned int realDirection = this->getRealAddress(pPointer->_d_pointer._memDirection);
	_mutex.lock();
	MemoryNode *node = _memoryList->find("ID", pPointer->_d_pointer._memDirection);
	_mutex.unlock();
	unsigned char message;

	//La memoria a asignar a sido reservada previamente por el mismo cliente
	if(node != NULL){//Se recorre la memoria guardando los bytes
		if(pPointer->_bytes <= node->getAmountMem()){
			unsigned char *tmp = (unsigned char*)realDirection;
			for(int i = 0; i<pPointer->_bytes; i++){// Se recorre la memoria borrando los bytes
				*(tmp+i) = pByteStream[i];
			}
			message = 0;
			return message;
		}
		else{
			message = 1;
			return message;
		}
	}
	//Si no se existe memoria reservada en la dirección enviada no se realiza la operación
	else{
		message = 1;
		return message;
	}
}



/**
 * @brief Método que obtiene el byteStream solicitado por el cliente
 *
 * Se obtiene la dirección real del espacio reservado en memoria, sumando la dirección
 * virtual enviada con la dirección real del inicio del espacio de reserva.
 *
 * Se busca en la lista si el cliente que solicita la operación a reservado previamente
 * la memoria en la dirección obtenida.
 *
 * Si le memoria a sido previamente reservada, se comprueba:
 *		** Si el cliente solicita una cantidad de bytes menor igual a la cantidad reservada,
 *		   la operación se lleva a cabo normalmente con un status de 0 indicando que fue exitosa.
 *		** Si el cliente solicita una cantidad de bytes mayor a la cantidad reservada, solo se
 *		   retornan los bytes que se habian reservado, con un status de 1 indicando que se intento
 *		   a memoria no reservada.
 *
 * Si la memoria no fue previamente reservada se retorna un status de 1 indicando un error
 *
 * @param pPointer Puntero a una struct de tipo d_pointer_size con los parametros del cliente
 *
 * @return Arreglo de tipo unsigned char con el status y el byteStream obtenido
 */
unsigned char *SDSMMemoryNode::d_get(d_pointer_size *pPointer){
	unsigned int realDirection = this->getRealAddress(pPointer->_d_pointer._memDirection);
	_mutex.lock();
	MemoryNode *node = _memoryList->find("ID", pPointer->_d_pointer._memDirection);
	_mutex.unlock();
	unsigned int status;
	unsigned int index;

	//Se a reservado espacio previamente por el cliente
	if(node != NULL){
		if(pPointer->_bytes <= node->getAmountMem()){
			index = pPointer->_bytes;
			status = 0;
		}
		else{ //Se intenta obtener mas bytes de los que han sido reservados
			index = node->getAmountMem();
			status = 1;
		}
		unsigned char *message = new unsigned char[index+1];
		unsigned char *tmp = (unsigned char*)realDirection;
		for(int i = 0; i<index; i++){ //Se recorre la memoria obteniendo los bytes
			message[i+1] = *(tmp+i);
		}
		message[0] = status;
		return message;
	}
	//No se a reservado memoria previamente por el cliente
	else{
		unsigned char *message = new unsigned char[1];
		message[0] = 1;
		return message;
	}
}



/**
 * @brief Método que retonar a los cliente la información sobre el uso de la memoria
 *
 * @return Arreglo con la cantidad de memoria total del SDS y la cantidad de memoria
 *		   que se esta utilizando
 */
unsigned char *SDSMMemoryNode::d_status(){

	unsigned char *status = new unsigned char[8];
	unsigned char *totalMem = this->intToBytes(_totalMem);
	unsigned char *inUse = this->intToBytes(_memUsed);

	unsigned int index = 0;
	for(; index < NUM_BYTES_INT; index++){
		status[index] = totalMem[index];
	}
	for(unsigned int index2 = 0; index < 8, index2 < NUM_BYTES_INT; index++, index2++){
		status[index] = inUse[index2];
	}

	return status;
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
	for(unsigned int i = 0; i < pBytes.length(); i+=HEX_LEN){
		std::string stringByte = pBytes.substr(i, 2);
		char *charByte = (char*)&stringByte[0u];
		unsigned int byte;
		sscanf(charByte, HEX_FORMAT, &byte);
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
		newInt += (byteArray[i] & 0xFF) << (BITS*j);
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
unsigned char *SDSMMemoryNode::intToBytes(unsigned int &pInt){
	unsigned char *bytes = new unsigned char[NUM_BYTES_INT];

	for(int index = ZERO, byte = ZERO; index < NUM_BYTES_INT, byte <= LAST_BYTE; index++, byte++){
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

	return (unsigned short) (((byteArray[pStartIndex] << BITS)) | ((byteArray[pEndIndex] & HEX_255)));
}


/**
 * @brief Método que convierte un short a su representación en bytes
 *
 * @param pShort Short al que quieren obtenerse los bytes
 *
 * @return Arreglo con los bytes
 */
unsigned char *SDSMMemoryNode::shortToBytes(unsigned short pShort){
	unsigned char *bytes = new unsigned char[HEX_LEN];

	bytes[0] = (pShort & 0xFF00) >> BITS;
	bytes[1] = pShort & 0x00FF;

	return bytes;
}



/**
 * @brief Método que llena un arreglo de tipo char con la direccion ip
 *
 * @param pArray Arreglo donde se guardara la ip
 */
void SDSMMemoryNode::getIP(unsigned char *pArray){
	unsigned char *bytes = (unsigned char*)_ip.c_str();

	char *tmp = strtok((char*)bytes, SPLIT_IP);

	for(int i = 0; i < sizeof(pArray); i++){
		std::string byte = (std::string)tmp;
		pArray[i] = std::stoi(byte);
		tmp = strtok(NULL, SPLIT_IP);
	}
}



/**
 * @brief Método que obtiene la dirección real en memoria
 *
 * A la dirección real donde comienza la memoria compartida se le suma
 * el offset de la memoria virtual para asi obtener la dirección real
 *
 * @param pVirtualDirection Offset de la memoria virtual
 *
 * @return Dirección real en memoria
 */
unsigned int SDSMMemoryNode::getRealAddress(unsigned int pVirtualAddress){
	return (_initDirection+pVirtualAddress);
}



/**
 * @brief Método que crea una struct d_pointer_size con los bytes enviados al servidor
 *
 * @param pByteArray Arreglo tipo unsigned char con los bytes
 *
 * @return Puntero a una struct d_pointer_size
 */
d_pointer_size *SDSMMemoryNode::setUpPointer(unsigned char *pByteArray){
	d_pointer_size *pointer = new d_pointer_size;
	for(int i = 0; i<NUM_BYTES_INT; i++){
		pointer->_d_pointer._ip[i] = pByteArray[i];
	}
	pointer->_d_pointer._port = *((unsigned short*)pByteArray+2);
	unsigned char *tmp = pByteArray+2;
	pointer->_d_pointer._memDirection = *((unsigned int*)tmp+1);
	pointer->_bytes = *((unsigned int*)tmp+2);

	return pointer;
}



/**
 * @brief Método que obtiene el nombre del método que debe ser ejecutado
 *
 * Convierte el buffer enviado por el servidor a tipo string en una  variable local,
 * luego se crea una variable de tipo stringstream, se recorre el string con los bytes
 * insertando en el stringstream el caracter de cada byte leido, hasta encontrar el byte
 * "3a" que corresponde el final del nombre del método, luego se obtiene el string con
 * el nombre, el cual es retornado.
 *
 * @param pBuffer Buffer con los bytes recibidos
 *
 * @return Nombre del método a ejecutar
 */
std::string SDSMMemoryNode::getMethod(unsigned char *pBuffer){
	std::string tempStr = (char const*)pBuffer;
	std::stringstream stream;
	for(unsigned int i=0; i < tempStr.length(); i+=HEX_LEN){
		std::string stringByte = tempStr.substr(i, HEX_LEN);
		if(stringByte == HEX_SPLIT) break;
		char _char = (char) (int)strtol(stringByte.c_str(), NULL, HEX_BASE);
		stream << _char;
	}
	std::string method = stream.str();

	return method;
}



/**
 * @brief Método que obtiene los bytes con los parametros que debe ser usados
 *
 * Se obtiene un string del buffer de bytes, el cual se recorre hasta encontrar
 * el byte "3a" correspondiente al final del nombre del método a ejecutar.
 * Luego se crea un puntero al indice del arreglo donde comienzan los bytes
 * parametro, sabiendo ya el indice donde terminan los bytes correspondientes
 * al nombre del método. Este los bytes a los que apunte este puntero creado
 * se castean a string y se retornan
 *
 * @param pBuffer Buffer con los bytes recibidos
 *
 * @return String que contiene los bytes parametro
 */
std::string SDSMMemoryNode::getByteStream(unsigned char *pBuffer){
	std::string tempStr = (char const*)pBuffer;
	std::stringstream stream;
	unsigned int i=0;
	for(; i < tempStr.length(); i+=HEX_LEN){
		std::string stringByte = tempStr.substr(i, HEX_LEN);
		if(stringByte == HEX_SPLIT) break;
	}
	unsigned char *bytes = pBuffer+(i+HEX_LEN);
	std::string strBytes = (char const*)bytes;

	return strBytes;
}




