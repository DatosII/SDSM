//#ifndef LINKEDLISTMD_H
//#define LINKEDLISTMD_H

//#include <string>
//#include <string.h>
//#include <iostream>
//#include <pthread.h>
//#include <time.h>
//#include <d_pointer_size_type.h>
//#include <xmlparser.h>
//#include <node_md.h>

//#define JUMP "\n"
//#define MESSAGE "DATO NO ENCONTRADO"

//using namespace std;

///**
// * @brief The parametrosGarbaje struct es
// * un struct con la propia lista y con la
// * frecuencia de revision.
// */
//struct parametrosGarbaje{
//    int frecuencia;
//    void* listaMetadatos;
//    void* pPunteroDHeap;
//};

///**
// * @file linkedlist.h
// * @brief Crea una lista simple enlazada
// * @author Juan Pablo Brenes Coto
// * @date 15/8/2015
// */
//class  LinkedListMD {

//public:
//    LinkedListMD(void *pPunteroDHeap, int pFrecuencia);
//    ~LinkedListMD();

//    Node_MD *getHead();
//    void insert(d_pointer_size_type pPointer);
//    void remove(d_pointer_size_type pPointer);
//    Node_MD* find(d_pointer_size_type pPointer);
//    void print();

//    /**
//    * @brief operator = Operador de asignacion para borrar
//    * datos de la memoria remota.
//    * @param pToFree puntero con los datos del objeto a borrar.
//    */
//    void operator = (const d_pointer_size_type pToFree);

//private:
//    Node_MD *_head;
//    Node_MD *_tail;
//    void* punterodHeap;
//    parametrosGarbaje* parametros;
//    pthread_t hiloGarbaje;
//    static void* garbajeCollector(void* pParametros);
//};

//#endif // LINKEDLISTMD_H
