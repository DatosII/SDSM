#include "SDSMMemoryNode/servidorsmsmm.h"
#include <time.h>


/**
 * @brief ServidorSMSMM::ServidorSMSMM. Constructor del servidor del SDSMM.
 *
 * Espera solicitudes de conexion a clientes para ser atendidos en send_receiveSDS
 */
ServidorSMSMM::ServidorSMSMM(const unsigned int pMemory, const char pUnit, const string pIP, const unsigned short pPort, const unsigned short pStatePort){

	/**Definimos los parametros que utilizaremos en cada hilo, siendo estos pasados
	por un struct*/
	parametro->mutex = PTHREAD_MUTEX_INITIALIZER;
	parametro->sdsm = new SDSMMemoryNode(pMemory, pUnit, pIP, pPort, pStatePort);

	parametrosvisor->mutex = parametro->mutex;
	parametrosvisor->sdsm = parametro->sdsm;
	parametrosvisor->puerto = pStatePort;

	pthread_create(&threadVisor,NULL,servidorVisor,parametrosvisor);

	/**Ciclo de espera de solicitudes */
	while (loop){
		int puerto = (int)pPort;
		int bufSize = 1024;
		int clientes,servido,pid;
		bool salir=false;
		char* buffer=new char[bufSize];
		struct sockaddr_in direc;
		socklen_t tamano;
		if ((clientes=socket(AF_INET,SOCK_STREAM,0))<0){
			cout<<"Se presento un error al crear el socket"<<endl;
			exit(1);
		}
		cout<<"Servidor ha sido creado"<<endl;
		direc.sin_family=AF_INET;
		direc.sin_addr.s_addr=htons(INADDR_ANY);
		direc.sin_port=htons(puerto);
		if ((bind(clientes,(struct sockaddr*)&direc,sizeof(direc)))<0){
			cout<<"Error en la conexion por Bind"<<endl;
		}
		else{
			cout<<"Conecte el cliente...../..\../..\../..\....."<<endl;
			listen(clientes,1);
			tamano=sizeof(direc);
			while(loop){
				servido=accept(clientes,(struct sockaddr *)&direc,&tamano);
				cout<< "Conexion con el cliente exitosa"<<endl;
				if(servido<0)
					cout<<"ERROR en aceptar"<<endl;
				pid = fork();
				/**Condicional que delega en un hilo al
				 *  servidor que acaba de conectar */
				if(pid == 0){
					close(clientes);
					parametro->socket = servido;
					send_receiveSDS(parametro);
					exit(0);
				}
			}
		}
		close(clientes);
	}
}

void* ServidorSMSMM::servidorVisor(void * arguments){
	bool loop = true;
	pthread_mutex_t mutex= ((parametrosVisor*)arguments)->mutex;
	SDSMMemoryNode* sdsmm = ((parametrosVisor*)arguments)->sdsm;
	int puerto = ((parametrosVisor*)arguments)->puerto;
	int bufSize = 1024;
	int clientes;
	bool salir=false;
	unsigned char* mensaje;
	/**Ciclo de espera de solicitudes */
	while (loop){
		//char* buffer=new char[bufSize];
		struct sockaddr_in direc;
		socklen_t tamano;
		if ((clientes=socket(AF_INET,SOCK_STREAM,0))<0){
			std::cout<<"Se presento un error al crear el socket"<<std::endl;
			exit(1);
		}
		std::cout<<"Servidor Visor ha sido creado"<<std::endl;
		direc.sin_family=AF_INET;
		direc.sin_addr.s_addr=htons(INADDR_ANY);
		direc.sin_port=htons(puerto);
		if ((bind(clientes,(struct sockaddr*)&direc,sizeof(direc)))<0){
			cout<<"Error en la conexion por Bind"<<endl;
		}
		else{
			cout<<"Conecte el Visor...../..\../..\../..\....."<<endl;
			listen(clientes,1);
			tamano=sizeof(direc);
			while(loop){
				clientes=accept(clientes,(struct sockaddr *)&direc,&tamano);
				pthread_mutex_lock(&mutex);
				mensaje = sdsmm->d_status();
				pthread_mutex_unlock(&mutex);
				close(clientes);
			}
		}
	}
}

/**
 * @brief ServidorSMSMM::timeOut Metodo que envia un mensaje al cliente para
 * conocer su estado actual (permanece conectado o no).
 *
 * @param pSocket numero de socket del que se desea conocer su estado.
 *
 * @return bool que indica si el cliente sigue conectado o no.
 */
bool ServidorSMSMM::timeOut(int pSocket){

	fd_set _readset;
	int _result, _iof = -1;
	struct timeval _time;

	// Initialize the set
	FD_ZERO(&_readset);
	FD_SET(pSocket, &_readset);

	/** Inicializamos el tiempo de espera del struct*/
	_time.tv_sec = 0;
	_time.tv_usec = 6000;

	/** Linea principal del algoritmo. Espera un mensaje en una
		cantidad determinada de tiempo. Deacuerdo al resultado
		retorna un numero*/
	_result = select(pSocket+1, &_readset, NULL, NULL, &_time);

	//cout<<_result<<endl;

	/** Retorna un resultado luego de esperar
	 *  una cantidad definida de tiempo por el mensaje*/
	if(_result >0)
		return true;
	if(_result <0)
		return false;
	else
		return false;
}


/**
 * @brief ServidorSMSMM::send_receiveSDS. Metodo que atiende a cada cliente
 * conectado al servidor. En cada uno de estos hilos se accede al SDSMM
 * mediante un Mutex(semaforo binario).Tambien corrobora si un cliente
 * se desconecto o no.
 *
 * @param pParametros es un struct con el numero de socket, el SDSMM y
 * el MUTEX
 *
 * @return Un puntero void.
 */
void* ServidorSMSMM::send_receiveSDS(parametrosCliente* pParametros){
	/** Definimos los parametros generales que utilizaremos para la
	 * recepcion y envio de mensajes, asi como variables de tiempo */
	int _socket = pParametros->socket;
	int _bufSize = 1024;
	//char* _buffer=new char[_bufSize];
	bool _loopMensajeria = true;
	int _initialTime = 0;
	int _finalTime=0;


	cout << "Hola mundo, yo soy el cliente numero " << _socket << endl;

	unsigned char message[] = D_STATUS;
	unsigned char *ptr = message;
	pthread_mutex_lock(&(pParametros->mutex));
	send(_socket, (char*)pParametros->sdsm->parser(ptr), _bufSize, 0);
	pthread_mutex_unlock(&(pParametros->mutex));

	_initialTime = time(NULL);
	_finalTime = time(NULL);

	//send(_socket, "Conectado a servidor",1024, 0);

	/** Ciclo que receibe y envia datos. Tambien Corrobora si la coneccion
	 * permanece cada cierta cantidad de tiempo  */
	while (_loopMensajeria){
		char* _buffer;
		if(_finalTime-_initialTime>500000000){
			send(_socket, "Estas conectado?",1024, 0);

			if(timeOut(_socket)){
				_initialTime = time(NULL);
			}
			else
				_loopMensajeria = false;
		}
		else{
			_buffer =new char[_bufSize];
			recv(_socket,_buffer,_bufSize,0);

			//cout<<_buffer<<endl;

			/** Entramos al sdsm por medio de un candado ya que este
			 * se encuentra compartida en cada uno de los clientes  */
			pthread_mutex_lock(&(pParametros->mutex));
			void *temp = (void*)_buffer;
			send(_socket, (char*)pParametros->sdsm->parser((unsigned char*)_buffer),_bufSize, 0);
			pthread_mutex_unlock(&(pParametros->mutex));

			_finalTime = time(NULL);
			delete _buffer;
		}
	}
}



/**
 * @brief ServidorSMSMM::~ServidorSMSMM. Destructor general de
 * la clase ServidorSDSMM
 */
ServidorSMSMM::~ServidorSMSMM(){
}
