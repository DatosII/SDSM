#ifndef DHEAP_H
#define DHEAP_H

#include <string>
#include <string.h>
#include <d_pointer_size_type.h>
#include <xmlparser.h>
#include <linkedlist.h>
#include <linkedlistmd.h>

using namespace std;

/**
 * @brief The dHeap class Clase que abstrae el concepto de memoria
 * compartiendola en sus diferentes servidores. Solo posee los
 * datos relativos a la localizacion de la informacion.
 */
class dHeap{

public:
    static dHeap* instancia(char* path);
    static dHeap* instancia();
    d_pointer_size_type dMalloc(int pSize, string pType);
    void dfree(d_pointer_size_type pPuntero);


private:
    char* path;
    xmlParser* lectorXML;
    static dHeap* miInstancia;
    LinkedListMD* metadatos;
    LinkedList* listaDeServidores;

    /** Declaracion de los metodos privados de nuestro dHeap*/
    dHeap(char* pPath);
    ~dHeap();

    /** Realizamos la sobrecarga del operador de igualdad*/
    dHeap* operator=(const dHeap heap);
};

#endif // DHEAP_H
