#ifndef DLINKEDLIST
#define DLINKEDLIST


#include "Structures/Nodes/node_dll.h"
#include <iostream>

#define JUMP "\n"
#define MESSAGE "NO ENCONTRE EL DATO"

/**
 * @file dlinkedlist.h
 * @brief Crea una lista doblemente enlazada
 * @author Juan Pablo Brenes
 * @date 29/8/2015
 */

template<class T>
    class  DLinkedList {

        public:
            DLinkedList(); //Constructor
            ~DLinkedList(); //Destructor
            Node_DLL<T> *getHead(); //Método para obtener el head
            void insert(const T& pData); //Método para insertar un dato
            void remove(const T& pData); //Método para eliminar un dato
            Node_DLL<T>* find(T pData); //Método para buscar un dato
            void print(); //Método para imprimir toda la lista

        private:
            Node_DLL<T> *_head;
            Node_DLL<T> *_tail;
    };



/*------------------------------------
 * -----------------------------------
 * DEFINICIÓN DE LA CLASE
 * -----------------------------------
 * -----------------------------------*/

    /**
     * @brief Constructor que inicializa los punteros al head y el tail como nulos
     */
    template <class T>
    DLinkedList<T>::DLinkedList(): _head(0), _tail(0) {}



    /**
     * @brief Método que permite insertar un nuevo dato en la lista
     *
     * @param pData Dato que se quiere insertar
     */
    template<class T>
    void DLinkedList<T>::insert(const T &pData) {

        Node_DLL<T> *newNode = new Node_DLL<T>(pData);

        if (_head == 0){
            _head = _tail = newNode;
        }

        else{
            Node_DLL<T> *tmp = _head;
            while((*tmp).getNext() != 0){
                tmp = tmp->getNext();
            }
            tmp->setNext(newNode);
            newNode->setPrev(tmp);
            _tail = newNode;
        }
    }



    /**
     * @brief Método que elimina un dato dentro de la lista
     *
     * Recorre la lista comparando el dato almacenado por cada nodo
     * con el dato que se quiere eliminar, cuando se encuentra el
     * nodo que almacena el dato, este es eliminado
     *
     * @param pData Dato que se quiere eliminar de la lista
     */
    template<class T>
    void DLinkedList<T>::remove(const T &pData){
        if(_head == 0) return;

        else if(_head->getData() == pData){
            Node_DLL<T> *temp = _head;
            _head = _head->getNext();
            delete temp;
        }
        else{
            Node_DLL<T> *tmp = _head->getNext();
            while(tmp != 0){
                if(tmp->getData() == pData){
                    tmp->getPrev()->setNext(tmp->getNext());
                    if(tmp == _tail) _tail = tmp->getPrev();
                    delete tmp;
                    break;
                }

               // prev = next;
                tmp = tmp->getNext();
            }
        }
    }



    /**
     * @brief Método que busca un dato dentro de la lista
     *
     * Recorre la lista comparando el dato almacenado en cada nodo
     * con el dato que se busca, si se encuentra el nodo que contiene
     * el dato, este se retorna; en caso constrario se retorna NULL
     *
     * @param pData Dato que se quiere buscar
     *
     * @return Nodo que contiene el dato buscado
     */
    template<class T>
    Node_DLL<T> *DLinkedList<T>::find(T pData){
        if(_head != 0){
            Node_DLL<T> *temp = _head;
            while(temp != 0){
                if(temp->getData() == pData) return temp;
                temp = temp->getNext();
            }
        }
        else{
            std::cout << MESSAGE << JUMP;
            return NULL;
        }
    }



    /**
     * @brief Método que retorna el head de la lista
     *
     * @return Head de la lista
     */
    template<class T>
    Node_DLL<T> *DLinkedList<T>::getHead() {
        return this->_head;
    }


    /**
     * @brief Método que imprime todos los datos almacenados dentro de la lista
     */
    template<class T>
    void DLinkedList<T>::print(){
        Node_DLL<T> *tmp = _head;
        while(tmp != 0){
            std::cout << tmp->getData() << JUMP;
            tmp = tmp->getNext();
        }
    }


    /**
     * @brief Destructor de la clase
     *
     * Recorre toda la lista borrando los punteros a cada nodo
     */
    template<class T>
    DLinkedList<T>::~DLinkedList(){
        if(_head != 0){
            Node_DLL<T> *current = _head;
            Node_DLL<T> *next;

            while(current->getNext() != 0){
                next = current->getNext();
                delete current;
                current = next;
            }
        }
    }


#endif // DLINKEDLIST




