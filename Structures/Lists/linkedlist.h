#ifndef LINKEDLIST
#define LINKEDLIST

#include "Nodes/node_ll.h"
#include <iostream>

#define JUMP "\n"
#define MESSAGE "DATO NO ENCONTRADO"

/**
 * @file linkedlist.h
 * @brief Crea una lista simple enlazada
 * @author Juan Pablo Brenes Coto
 * @date 15/8/2015
 */

template<class T>
    class  LinkedList {

        public:
            LinkedList();
            ~LinkedList();

            Node_LL<T> *getHead();
            void insert(const T& pData);
            void remove(const T& pData);
            Node_LL<T>* find(T pData);
            void print();

        private:
            Node_LL<T> *_head;
            Node_LL<T> *_tail;
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
    LinkedList<T>::LinkedList(): _head(0), _tail(0) {}



    /**
     * @brief Método que permite insertar un nuevo dato en la lista
     *
     * @param pData Dato que se quiere insertar dentro de la lista
     */
    template<class T>
    void LinkedList<T>::insert(const T &pData) {

        Node_LL<T> *newNode = new Node_LL<T>(pData);

        if (_head == 0){
            _head = _tail = newNode;
        }

        else{
            Node_LL<T> *tmp = _head;
            while((*tmp).getNext() != 0){
                tmp = tmp->getNext();
            }
            tmp->setNext(newNode);
            _tail = tmp;
        }
    }



    /**
     * @brief Método que elimina un dato dentro de la lista
     *
     * Recorre la lista comparando el dato almacenado por cada nodo
     * con el dato que se quiere eliminar, cuando se encuentra el
     * nodo que almacena el dato, este es eliminado
     *
     * @param pData Dato que se quiere borrar de la lista
     */
    template<class T>
    void LinkedList<T>::remove(const T &pData){
        if(_head == 0){ //Lista esta vacia
            return;
        }
        else if(_head->getData() == pData){ //Dato se encuentra en el head
            Node_LL<T> *temp = _head;
            _head = _head->getNext();
            delete temp;
        }
        else{ //Dato no esta en el head, se debe buscar
            Node_LL<T> *prev = _head, *next = _head->getNext();
            while(next != 0){
                if(next->getData() == pData){
                    prev->setNext(next->getNext());

                    if(next == _tail){
                        _tail = prev;
                    }
                    delete next;
                    break;
                }

                prev = next;
                next = next->getNext();
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
     * @param pData Dato que se quiere buscar dentro de la lista
     *
     * @return Nodo que contiene el dato buscado
     */
    template<class T>
    Node_LL<T> *LinkedList<T>::find(T pData){
        if(_head != 0){
            Node_LL<T> *temp = _head;
            while(temp != 0){
                if(temp->getData() == pData){
                    return temp;
                }
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
    Node_LL<T> *LinkedList<T>::getHead() {
        return this->_head;
    }


    /**
     * @brief Método que imprime todos los datos almacenados dentro de la lista
     */
    template<class T>
    void LinkedList<T>::print(){
        Node_LL<T> *tmp = _head;
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
    LinkedList<T>::~LinkedList(){
        if(_head != 0){
            Node_LL<T> *current = _head;
            Node_LL<T> *next;

            while(current->getNext() != 0){
                next = current->getNext();
                delete current;
                current = next;
            }
        }
    }


#endif // LINKEDLIST

