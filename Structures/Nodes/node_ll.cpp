#include <node_ll.h>

/**
 * @brief Constructor que recibe como parametro el dato que el nodo va a almacenar
 *
 * @param Dato que almacenara el nodo
 */
Node_LL::Node_LL(const std::string &pData1, const std::string &pData2, void *pPuntero){

    parametros = new parametrosInicioCliente();

    this->_IP = (char*)pData1.c_str();
    this->_PUERTO = atoi(pData2.c_str());
    this->_next = 0;

    parametros->IP = this->_IP;
    parametros->PUERTO = this->_PUERTO;
    parametros->punterodHeap = pPuntero;

    //Creamos el hilo que ejecutara la coneccion con el SDS que se especifico con
    //el ip y puerto que se pasaron como parametros.
        pthread_create(&hiloCliente,NULL,conectarClientes,parametros);

}



/**
 * @brief Método que retorna el dato almacenado por el nodo
 *
 * @return Dato almacenado por el nodo
 */

char* Node_LL::getData() {
    return this->_IP;
}



/**
 * @brief Método que permite obtener el siguiente nodo
 *
 * @return Nodo siguiente
 */
Node_LL *Node_LL::getNext() {
    return this->_next;
}



/**
 * @brief Método que permite establecer el siguiente nodo
 *
 * @param pNext Nodo siguiente
 */
void Node_LL::setNext(Node_LL *pNext) {
    this->_next = pNext;
}

/**
 * @brief Hilo del cliente.
 */
void* Node_LL::conectarClientes(void* pParametros){
    char a;
    int cliente;
    int puerto=((parametrosInicioCliente*)pParametros)->PUERTO;
    int bufsize=1024;
    char* buffer=new char(bufsize);
    bool salir =false;
    char* ip;
    strcpy(ip,((parametrosInicioCliente*)pParametros)->IP);

    struct sockaddr_in direc;
    if ((cliente=socket(AF_INET,SOCK_STREAM,0))<0){
        std::cout<<"Error al crear el socket cliente"<<std::endl;
        exit(0);
    }

    direc.sin_family=AF_INET;
    direc.sin_port=htons(puerto);
    inet_pton(AF_INET,ip,&direc.sin_addr);

    if (connect(cliente,(struct sockaddr *)&direc,sizeof(direc))==0){
        std::cout<<"Conexion con el servidor"<<inet_ntoa(direc.sin_addr)<<std::endl;
    }

    std::cout<<"Esperando confirmacion del servidor"<<std::endl;
    recv(cliente,buffer,bufsize,0);

    std::cout<<"Respuesta recibida: "<<buffer;

    while(true){
        if(5==5/** En esta parte debo incluir que si existe algo para mandar por el dHeap que lo envie*/){

        }
        else{/** En esta parte le digo que espere el mensaje que envia cotidianamente el servidor para conocer
              si todavia existe coneccion con el cliente*/

        }
    }
    std::cout<<"Conexion terminada. Coneccion con el SDS  finalizo\n\n";
    close(cliente);
}
