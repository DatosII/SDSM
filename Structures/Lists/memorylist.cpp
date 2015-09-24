#include "Structures/Lists/memorylist.h"




/**
 * @brief Constructor de la clase
 *
 * Inicializa el head y el tail en 0, asi como los enteros que indican, la posición de memoria
 * donde comienza el espacio compartido y el total de memoria a compartir en bytes
 *
 * @param pInitMem Entero que indica la posición de memoria desde donde comienza compartir
 * @param pTotalMem Cantidad total de memoria para compartir (bytes)
 *
 */
MemoryList::MemoryList(unsigned int pInitMem, unsigned int pTotalMem){
    _head = 0;
    _tail = 0;
    _initMem = pInitMem;
    _totalMem = pTotalMem;
}



/**
 * @brief Método que retorna el head de la lista
 *
 * @return Head de la lista
 */
MemoryNode *MemoryList::getHead(){
    return _head;
}



/**
 * @brief Método que retorna la cantidad de nodos dentro de la lista
 *
 * La cantidad de nodos dentro de la lista indica el número de datos
 * el o los clientes han reservado
 *
 * @return Cantidad de nodos dentro de la lista
 */
unsigned int MemoryList::getTotalNodes(){
    return _totalNodes;
}



/**
 * @brief Método que permite reservar espacios en la memoria para los clientes
 *
 * Se comprueba si el head es nulo, si lo es entonces se reserva la memoria en el inicio
 * Si el head no es nulo, se comprueba si hay espacio suficiente entre el inicio de la memoria
 * y el primer espacio reservado, si hay espacio se inserta en el head, si no hay espacio
 * se llama al método auxiliar
 *
 * @see MemoryList::insertAux()
 *
 * @param pNode Nodo que se quiere insertar (espacio de memoria a reservar)
 *
 * @return Puntero a un arreglo de tipo unsigned int con dos valores:
 *          *Primer valor: 0 si se reservo espacio, 1 si no hay espacio
 *          *Segundo valor: dirección de memoria del espacio reservado
 */
unsigned int *MemoryList::insert(MemoryNode *pNode){
    //No se a reservado ningun espacio
    if(_head == 0){
        _head = _tail = pNode;
        pNode->setInitMem(_initMem);
        _totalNodes++;
        unsigned int values[] = {0,_initMem};
        return values;
    }
    else{
        //Se comprueba espacio entre la primera reserva y el inicio de la memoria
        if( (_head->getInitMem()-_initMem) >= pNode->getAmountMem()){
            pNode->setInitMem(_initMem);
            _head->setPrev(pNode);
            pNode->setNext(_head);
            _head = pNode;
            _totalNodes++;
            unsigned int values[] = {0,_initMem};
            return values;
        }
        //Se debe buscar espacio, se llama el método auxiliar
        else{
            return this->insertAux(pNode);
        }
    }
}



/**
 * @brief Método auxiliar para insertar
 *
 * Se crean dos punteros (current y next) que apuntan al nodo actual (current) y
 * a su nodo siguiente (next), y dos variables las cuales almacenan:
 *      *prevEndMem: Dirección donde termina el espacio reservado por prev
 *      *nextInitMem: Dirección donde comienza el espacio reservado por current
 *
 * Se recorre de manera iterativa la lista comprobando si existe espacio suficiente
 * entre prev y current (nextInitMem - prevEndMem) donde se pueda reservar el espacio
 * solicitado por pNode.
 *
 * Se sale de la iteración si: se alcanza el final de la lista o cuando se encuentra un
 * espacio entre prev y current
 *
 * Al salir de la iteracion se comprueba:
 *      *Si next != 0: Se encontro un espacio, se inserta pNode en medio de prev y current
 *      *Si next == 0: Se comprueba si todavio existe espacio para reservar entre el tail
 *                     y el final de la memoria disponible para compartir. Si hay espacio
 *                     se inserta pNode despues del tail, si no hay mas espacio no se
 *                     reserva mas memoria.
 *
 * @param pNode Nodo a insertar (espacio de memoria a reservar)
 *
 * @return Puntero a un arreglo de tipo unsigned int con dos valores:
 *          *Primer valor: 0 si se reservo espacio, 1 si no hay espacio
 *          *Segundo valor: dirección de memoria del espacio reservado
 */
unsigned int *MemoryList::insertAux(MemoryNode *pNode){
    MemoryNode *current = _head;
    MemoryNode *next = _head->getNext();
    unsigned int prevEndMem = (current->getInitMem()+current->getAmountMem());
    unsigned int nextInitMem = next->getInitMem();

    //Se comprueba si hay espacios de memoria libres entre los nodos
    while(next != 0){
        if((nextInitMem - prevEndMem) >= pNode->getAmountMem()){
            break;
        }
        else{
            next = next->getNext();
            nextInitMem = next->getInitMem();
            current = current->getNext();
            prevEndMem = (current->getInitMem()+current->getAmountMem());
        }
    }

    //Se encontro un espacio libre entre los nodos
    if( next != 0){
        pNode->setInitMem( (current->getInitMem()+current->getAmountMem()));
        pNode->setPrev(current);
        current->setNext(pNode);
        pNode->setNext(next);
        next->setPrev(pNode);
        _totalNodes++;
        unsigned int values[] = {0, pNode->getInitMem()};
        return values;
    }

    //No se encontro ningun espacio vacio entre nodos
    //Se comprueba si todavia hay espacio para reservar al final
    else{
        unsigned int endMem = (_initMem+_totalMem);
        unsigned int tailEndMem = (_tail->getInitMem()+_tail->getAmountMem());

        //Hay espacio para reservar al final, se inserta en el tail
        if( (endMem - tailEndMem) >= pNode->getAmountMem()){
            pNode->setInitMem(tailEndMem);
            pNode->setPrev(_tail);
            _tail->setNext(pNode);
            _tail = pNode;
            _totalNodes++;
            unsigned int values[] = {0,pNode->getInitMem()};
            return values;
        }

        //No hay mas espacio para reservar
        else{
            unsigned int values[] = {1,0};
            return values;
        }
    }
}



/**
 * @brief Método que busca un nodo en la lista
 *
 * Este método por d_free, d_get y d_set, para validar que se esta accediendo a un espacio
 * de memoria permitido
 *
 * @param pID ID del cliente
 * @param pMemAddress Dirección del espacio de memoria reservado
 *
 * @return Nodo que almacena la dirección en memoria y el ID que se busca
 *         Si no se encuentra ningun nodo se retorna NULL
 */
MemoryNode *MemoryList::find(std::string pID, unsigned int pMemAddress){
    //Se comprueba que la lista no este vacia
    if(_head != 0){

        MemoryNode *temp = _head;
        //Se recorre la lista
        while(temp != 0){
            //Se verifica la dirección de memoria
            if(temp->getInitMem() == pMemAddress){
                //Se verifica el ID del cliente
                if(temp->getID() == pID){
                    return temp;
                }
                else{
                    return NULL;
                }
            }
            temp = temp->getNext();
        }
        return NULL;
    }

    else{
        return NULL;
    }
}
