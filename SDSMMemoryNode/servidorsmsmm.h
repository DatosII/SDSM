#ifndef SERVIDORSMSMM_H
#define SERVIDORSMSMM_H

#include <sdsm.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <time.h>

using namespace std;

/**
 * @brief The parametrosCliente struct struct por el que enviaremos cada
 * hilo la informacion para que pueda atender a cada cliente
 */
struct parametrosCliente{
    int socket;
    pthread_mutex_t mutex;
    SDSM* sdsm;
};

/**
 * @brief The ServidorSMSMM class. Clase que recibira solicitudes atendera
 *  cada uno de los clientes y almacenara un nodo con la informacion que
 *  cada uno de los clientes le pida guardar.
 */
class ServidorSMSMM{
    bool loop =true;
    parametrosCliente* parametro = new parametrosCliente();
    int x = 0;

public:
    ServidorSMSMM();
    ~ServidorSMSMM();
private:
    static bool timeOut(int  pSocket);
    void* send_receiveSDS(parametrosCliente* pParametros);
};

#endif // SERVIDORSMSMM_H
