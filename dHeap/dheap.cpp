//#include "dheap.h"

//dHeap* dHeap::miInstancia = 0;

///**
// * @brief dHeap::operator = Sobrecarga del operador de
// * igualdad que evita alguna copia del dHeap.
// * @param heap es el objeto dHeap que se desea sobreescribir.
// * @return un objeto del tipo dHeap.
// */
//dHeap* dHeap::operator =(const dHeap heap){
//    return miInstancia;
//}


//dHeap::dHeap(char* pPath)
//{
//    path =pPath;
////    lectorXML = new xmlParser();
//    metadatos = new LinkedListMD(this, 1);////////////////////El uno hay que cambiarlo por la frecuecia del GC cuando se
//    listaDeServidores = new LinkedList(this);             ///solucione lo del XML.
////    lectorXML->getNodes(listaDeServidores);
//}

///**
// * @brief dHeap::instancia Metodo que limita el numero
// * de instancias de esta clase a solo una.
// * @param path es la ruta del archivo de configuracion.
// * @return un objeto dHeap.
// */
//dHeap* dHeap::instancia(char* path)
//{
//    if (miInstancia == 0)
//        miInstancia = new dHeap(path);
//    return miInstancia;
//}

///**
// * @brief dHeap::instancia metodo sobrecargado que
// * retorna la instancia unica del dHeap
// * @return un puntero del dHeap
// */
//dHeap* dHeap::instancia()
//{
//    return miInstancia;
//}


//d_pointer_size_type dHeap::dMalloc(int pSize, string pType)
//{

//}

//void dHeap::dfree(d_pointer_size_type pPuntero)
//{

//}


///**
// * @brief dHeap::~dHeap Destructor por defecto
// * de nuestra clase.
// */
//dHeap::~dHeap()
//{

//}
