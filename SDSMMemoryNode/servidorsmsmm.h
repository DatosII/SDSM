#ifndef SERVIDORSMSMM_H
#define SERVIDORSMSMM_H

#include "SDSMMemoryNode/SDSMMemoryNode.h"
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

#define D_STATUS "645f7374617475733a"

using namespace std;

/**
 * @brief The parametrosCliente struct struct por el que enviaremos cada
 * hilo la informacion para que pueda atender a cada cliente
 */
struct parametrosCliente{
	int socket;
	pthread_mutex_t mutex;
	SDSMMemoryNode* sdsm;
	unsigned char* mensaje;
	void* server =this;
};

struct parametrosVisor{
	int puerto;
	pthread_mutex_t mutex;
	SDSMMemoryNode* sdsm;
	void* server = this;
};


/**
 * @brief The ServidorSMSMM class. Clase que recibira solicitudes atendera
 *  cada uno de los clientes y almacenara un nodo con la informacion que
 *  cada uno de los clientes le pida guardar.
 */
class ServidorSMSMM{
	unsigned char* mensajeVisor =((unsigned char*)"0");
	bool loop =true;
	parametrosCliente* parametro = new parametrosCliente();
	parametrosVisor* parametrosvisor = new parametrosVisor();
	int x = 0;
	pthread_t threadVisor;

public:
	ServidorSMSMM(const unsigned int pMemory, const char pUnit, const std::string pIP, const unsigned short pPort, const unsigned short pStatePort);
	~ServidorSMSMM();
private:
	static bool timeOut(int  pSocket);
	void* send_receiveSDS(parametrosCliente* pParametros);
	static void* servidorVisor(void*arguments);
	unsigned char* prueba(parametrosCliente* pParametros);
};

#endif // SERVIDORSMSMM_H
