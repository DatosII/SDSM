#ifndef NODE_DLL
#define NODE_DLL



/**
 * @file node_dll.h
 * @brief Crea un nodo para ser utilizado por la lista doble
 * @author Juan Pablo Brenes
 * @date 29/8/2015
 */

template<class T>
    class Node_DLL{
    public:
        //Constructor
        Node_DLL();
        Node_DLL(const T &pData);

        //Getter y Setter del dato
        T getData();

        //Getter y Setter del siguiente nodo
        Node_DLL<T> *getNext();
        Node_DLL<T> *getPrev();
        void setNext(Node_DLL *pNext);
        void setPrev(Node_DLL *pPrev);

    private:
        T _data;
        Node_DLL<T> *_next, *_prev;
    };

#endif // NODE_DLL



/*------------------------------
 * -----------------------------
 * DEFINICIÓN DE LA CLASE
 * -----------------------------
 * -----------------------------*/

    /**
     * @brief Constructor sin parametros de la clase
     */
    template<class T>
    Node_DLL<T>::Node_DLL(){
    }



    /**
     * @brief Constructor que recibe como parametro el dato que el nodo va a almacenar
     *
     * @param pData Dato que almacenara el nodo
     */
    template<class T>
    Node_DLL<T>::Node_DLL(const T &pData){
        this->_data = pData;
        this->_next = 0;
        this->_prev = 0;
    }



    /**
     * @brief Método que retorna el dato almacenado por el nodo
     *
     * @return Dato almacenado por el nodo
     */
    template<class T>
    T Node_DLL<T>::getData() {
        return this->_data;
    }



    /**
     * @brief Método que permite obtener el siguiente nodo
     *
     * @return Nodo siguiente
     */
    template<class T>
    Node_DLL<T> *Node_DLL<T>::getNext() {
        return this->_next;
    }



    /**
     * @brief Método que permite establecer el siguiente nodo
     *
     * @param pNext Nodo siguiente
     */
    template<class T>
    void Node_DLL<T>::setNext(Node_DLL<T> *pNext) {
        this->_next = pNext;
    }



    /**
     * @brief Método que retorna el nodo anterior
     *
     * @return Nodo anterior
     */
    template<class T>
    Node_DLL<T> *Node_DLL<T>::getPrev(){
        return this->_prev;
    }



    /**
     * @brief Método que permite establecer el nodo anterior
     *
     * @param pPrev Nodo anterior
     */
    template<class T>
    void Node_DLL<T>::setPrev(Node_DLL *pPrev){
        this->_prev = pPrev;
    }





