#ifndef NODE_BST
#define NODE_BST

/**
 * @file node_bst.h
 * @brief Crea un nodo para ser utiliado por un árbol binario
 * @author Juan Pablo Brenes
 * @date 5/9/2015
 */

template<class T>
class Node_BST{

private:
    T _data; //Dato que almacena el nodo
    Node_BST<T> *_Hizq, *_Hder, *_parent; //Hijo izquierdo, derecho y padre del nodo

public:
    Node_BST(); //Constructor sin parametros
    Node_BST(const T& pData); //Constructor que recibe el dato a almacenar
    ~Node_BST(); //Destructor

    void setHder(Node_BST *pHder); //Método asignar el hijo derecho
    Node_BST<T> *getHder(); //Método para obtener el hijo derecho

    void setHizq(Node_BST *pHizq); //Método para asignar el hijo izquierdo
    Node_BST<T> *getHizq(); //Método para obtener el hijo izquierdo

    void setParent(Node_BST *pParent); //Método para asignar el padre
    Node_BST<T> *getParent(); //Método para obtener el padre

    bool hasHizq(); //Método que verifica si tiene hijo izquierdo
    bool hasHder(); //Método que verificasi tiene hijo derecho

    T getData(); //Método obtener el dato
};

#endif // NODE_BST


/* ------------------------------------------
 * DEFINICION DE LA CLASE
 * ------------------------------------------*/

/**
 * @brief Constructor por defecto de la clase
 */
template<class T>
Node_BST<T>::Node_BST(){
    this->_parent = 0;
    this->_Hizq = 0;
    this->_Hder = 0;
}


/**
 * @brief Constructor que recibe el dato que se quiere almacenar como parametro
 *
 * @param pData Dato que almacenara el nodo
 */
template<class T>
Node_BST<T>::Node_BST(const T& pData){
    this->_data = pData;
    this->_parent = 0;
    this->_Hizq = 0;
    this->_Hder = 0;
}


/**
 * @brief Método que retorna el dato almacenado por el nodo
 *
 * @return T Dato que almacena el nodo
 */
template<class T>
T Node_BST<T>::getData(){
    return this->_data;
}


/**
 * @brief Método que permite establecer el hijo izquierdo del nodo
 *
 * @param pHizq Nodo que sera el hijo izquierdo
 */
template<class T>
void Node_BST<T>::setHizq(Node_BST *pHizq){
    this->_Hizq = pHizq;
}



/**
 *@brief Método que permite obtener el hijo izquierdo del nodo
 *
 * @return Hijo izquierdo del nodo
 */
template<class T>
Node_BST<T> *Node_BST<T>::getHizq(){
    return this->_Hizq;
}


/**
 *@brief Método que permite obtener el hijo derecho del nodo
 *
 * @param pHder Nodo que sera el hijo derecho
 */
template<class T>
void Node_BST<T>::setHder(Node_BST *pHder){
    this->_Hder = pHder;
}



/**
 * @brief Método que permite obtener el hijo derecho del nodo
 *
 * @return Hijo derecho del nodo
 */
template<class T>
Node_BST<T> *Node_BST<T>::getHder(){
    return this->_Hder;
}


/**
 * @brief Método que permite establecer el padre del nodo
 *
 * @param pParent Nodo que sera el padre
 */
template<class T>
void Node_BST<T>::setParent(Node_BST *pParent){
    this->_parent = pParent;
}



/**
 * @brief Método que permite obtener el padre del nodo
 *
 * @return Padre del nodo
 */
template<class T>
Node_BST<T> *Node_BST<T>::getParent(){
    return this->_parent;
}


/**
 * @brief Método que permite saber si el nodo tiene hijo izquierdo
 *
 * @return True si tiene hijo izquierdo, false en caso contrario
 */
template<class T>
bool Node_BST<T>::hasHizq(){
    return (this->_Hizq != 0);
}


/**
 * @brief Método que permite saber si el nodo tiene hijo derecho
 *
 * @return True si tiene hijo derecho, false en caso contrario
 */
template<class T>
bool Node_BST<T>::hasHder(){
    return (this->_Hder != 0);
}


template<class T>
Node_BST<T>::~Node_BST(){
    this->_Hder = 0;
    this->_Hizq = 0;
    this->_parent = 0;
}






