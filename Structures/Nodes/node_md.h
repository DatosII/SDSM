#ifndef NODE_MD
#define NODE_MD

#include <iostream>
#include <pthread.h>
#include <d_pointer_size_type.h>

/**
 * @file node_ll.h
 * @brief Crea un nodo para ser utilizado por la lista simple
 * @author Juan Pablo Brenes
 * @date 15/8/2015
 */

    class Node_MD{
    public:
        //Constructor
        Node_MD(d_pointer_size_type pPointer);

//        Getter y Setter del dato
        d_pointer_size_type* getData();

        //Getter y Setter del siguiente nodo
        Node_MD *getNext();
        void setNext(Node_MD *pNext);

    private:
        d_pointer_size_type* dPointer;
        Node_MD *_next;
    };

#endif // NODE_LL
