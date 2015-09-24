#ifndef QUEUE
#define QUEUE

#include "Structures/Nodes/node_ll.h"
#include <iostream>

/**
 * @file queue.h
 * @brief Crea una cola
 * @author Juan Pablo Brenes
 * @date 7/9/2015
 */

template<class T>
class Queue{
private:
    Node_LL<T> *_head, *_tail;

public:
    Queue(); //Constructor
    ~Queue(); //Destructor

    void enqueue(const T& pData); //Método para enconlar un dato
    Node_LL<T> *dequeue(); //Método para des encolar un dato

    bool isEmpty(); //Método para saber si la cola esta vacía
    void print(); //Método qye imprime todos los datos de la cola
};

#endif // QUEUE


/*-----------------------------
 * ----------------------------
 * DEFINICIÓN DE LA CLASE
 * ----------------------------
 * ----------------------------*/


/**
 * @brief Constructor de la clase
 *
 * Inicializa el head y el tail en 0
 */
template<class T>
Queue<T>::Queue(){
    this->_head = 0;
    this->_tail = 0;
}



/**
 * @brief Método para encolar un dato dentro de la cola
 *
 * Si la cola esta vacia, el head y el tail apuntan al nuevo nodo creado
 * Si la cola no esta vacia, se inserta el nuevo nodo al final de la cola,
 * en el tail
 *
 * @param pData Dato que se quiere encolar
 */
template<class T>
void Queue<T>::enqueue(const T &pData){
    Node_LL<T> *newNode = new Node_LL<T>(pData);
    if(this->_head == 0){
       this->_head = this->_tail = newNode;
    }

    else{
        this->_tail->setNext(newNode);
        this->_tail = this->_tail->getNext();
    }
}



/**
 * @brief Método para des encolar un dato de la cola
 *
 * Si la cola esta vacia se retorna 0, si no esta vacía se crea un nodo
 * temporal que apunta al head y se comprueba si el head y el tail son iguales;
 * si los son ambos pasan a ser 0 y se retorna el temporal. Si no son iguales
 * el head pasa a apuntar al nodo siguiente y se retorna el temporal
 *
 * @return Primer nodo de la cola
 */
template<class T>
Node_LL<T> *Queue<T>::dequeue(){
    if(this->_head == 0) return 0;

    else{
        Node_LL<T> *tmp = this->_head;
        if(this->_head == this->_tail){
            this->_head = this->_tail = 0;
            tmp->setNext(0);
            return tmp;
        }
        else{
            this->_head = this->_head->getNext();
            tmp->setNext(0);
            return tmp;
        }
    }
}



/**
 * @brief Método para verificar si la cola esta vacía
 *
 * @return true si la cola esta vacia, false si no lo esta
 */
template<class T>
bool Queue<T>::isEmpty(){
    return (this->_head == 0);
}



/**
 * @brief Método que imprime los datos de la cola
 */
template<class T>
void Queue<T>::print(){
    Node_LL<T> *tmp =  this->_head;
    while(tmp != 0){
        std::cout << tmp->getData() << "\n";
        tmp = tmp->getNext();
    }
}



/**
 * @brief Destructor de la cola
 *
 * Si la cola no esta vacia, se recorren todos los nodos de la cola, borrandolos
 */
template<class T>
Queue<T>::~Queue(){
    if(_head != 0){
        Node_LL<T> *current = this->_head;
        Node_LL<T> *next;

        while(current->getNext() != 0){
            next = current->getNext();
            delete current;
            current = next;
        }
    }
}




