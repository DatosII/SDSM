#ifndef NODE_LL
#define NODE_LL

/**
 * @file node_ll.h
 * @brief Crea un nodo para ser utilizado por la lista simple
 * @author Juan Pablo Brenes
 * @date 15/8/2015
 */

template<class T>
    class Node_LL{
    public:
        //Constructor
        Node_LL();
        Node_LL(const T &pData);

        //Getter y Setter del dato
        T getData();

        //Getter y Setter del siguiente nodo
        Node_LL<T> *getNext();
        void setNext(Node_LL *pNext);

    private:
        T _data;
        Node_LL<T> *_next;
    };

#endif // NODE_LL



/*----------------------------
 * ---------------------------
 * DEFINICIÓN DE LA CLASE
 * ---------------------------
 * ---------------------------*/

    /**
     * @brief Constructor sin parametros de la clase
     */
    template<class T>
    Node_LL<T>::Node_LL(){
    }



    /**
     * @brief Constructor que recibe como parametro el dato que el nodo va a almacenar
     *
     * @param Dato que almacenara el nodo
     */
    template<class T>
    Node_LL<T>::Node_LL(const T &pData){
        this->_data = pData;
        this->_next = 0;
    }



    /**
     * @brief Método que retorna el dato almacenado por el nodo
     *
     * @return Dato almacenado por el nodo
     */
    template<class T>
    T Node_LL<T>::getData() {
        return this->_data;
    }



    /**
     * @brief Método que permite obtener el siguiente nodo
     *
     * @return Nodo siguiente
     */
    template<class T>
    Node_LL<T> *Node_LL<T>::getNext() {
        return this->_next;
    }



    /**
     * @brief Método que permite establecer el siguiente nodo
     *
     * @param pNext Nodo siguiente
     */
    template<class T>
    void Node_LL<T>::setNext(Node_LL<T> *pNext) {
        this->_next = pNext;
    }




