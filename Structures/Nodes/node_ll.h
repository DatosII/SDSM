#ifndef NODE_LL
#define NODE_LL

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>

/**
 *Template que usaremos para pasar los parametros que se
 * necesitan para crear la comunicacion cliente con servidor.
 */

struct parametrosInicioCliente{
    char* IP;
    int PUERTO;
    void* punterodHeap;
};


/**
 * @file node_ll.h
 * @brief Crea un nodo para ser utilizado por la lista simple
 * @author Juan Pablo Brenes
 * @date 15/8/2015
 */

    class Node_LL{
    public:
        //Constructor
        Node_LL();
        Node_LL(const std::string &pData1, const std::string &pData2, void* pPuntero);

//        Getter y Setter del dato
        char* getData();

        //Getter y Setter del siguiente nodo
        Node_LL *getNext();
        void setNext(Node_LL *pNext);

    private:
        char* _IP;
        int _PUERTO;
        pthread_t  hiloCliente;
        Node_LL *_next;
        parametrosInicioCliente* parametros;
        static void* conectarClientes(void *pParametros);
    };

#endif // NODE_LL
