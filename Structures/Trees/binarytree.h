#ifndef BINARYTREE
#define BINARYTREE

#include "Nodes/node_bst.h"
#include "Lists/queue.h"
#include <iostream>

#define JUMP "\n"
#define MESSAGE "DATO DUPLICADO NO INSERTADO"


/**
 * @file binarytree.h
 * @brief Crea un árbol binario generico
 * @author Juan Pablo Brenes
 * @date 5/9/2015
 */


template<class T>
class BinaryTree{

private:
    Node_BST<T> *_root; //Raíz del árbol
    int _totalNodes; //Cantidad de nodos

    void insertAux(Node_BST<T> *pRoot, Node_BST<T> *pNode); //Método insertar auxiliar
    Node_BST<T> *searchAux(Node_BST<T> *pRoot, const T& pData);
    void removeAux(Node_BST<T> *pNode); //Método remove auxiliar
    Node_BST<T> *maxMin(Node_BST<T> *pNode); //Método que busca el nodo mayor a la izquierda
    void printAux(Queue< Node_BST<T> > *pQueue); //Método para imprimir auxiliar


public:
    BinaryTree(); //Constructor sin parametros
    ~BinaryTree(); //Destructor

    Node_BST<T> *getRoot(); //Método para obtener la raíz

    void insert(const T& pData); //Método para inserta un nuevo dato
    void remove(const T& pData); //Método que borra un dato dentro del árbol
    Node_BST<T> *search(const T& pData);

    int getTotalNodes(); //Método que indica  la cantidad total de nodos
    void print(); //Método para imprimir los datos del árbol


};

#endif // BINARYTREE


/*---------------------------------------------
 * --------------------------------------------
 * DEFINICION DE LA CLASE
 * --------------------------------------------
 * --------------------------------------------*/



/**
 * @brief Constructor de la clase
 *
 * Inicializa el puntero a la raíz del árbol en 0
 */
template<class T>
BinaryTree<T>::BinaryTree(){
    this->_root = 0;
    this->_totalNodes = 0;
}



/**
 * @brief Método para  inserta un dato dentro del árbol
 *
 * Si la raíz del árbol es 0, se crea un nodo en la raíz que el cual
 * almacenara el dato. Si la raíz no es 0 se llama al método auxiliar
 *
 * @param pData Dato que se quiere almacenar dentro del árbol
 */
template<class T>
void BinaryTree<T>::insert(const T &pData){

    Node_BST<T> *newNode = new Node_BST<T>(pData);
    if(this->_root == 0){
        this->_root = newNode;
        _totalNodes++;
    }
    else this->insertAux(this->_root, newNode);
}



/**
 * @brief Método de insertar auxiliar
 *
 * Si el dato del nuevo nodo (pNode) es menor al dato de la raíz (pRoot)
 * se comprueba si el hijo izquierdo de la raíz es nulo, si lo es, el nuevo
 * nodo pasa a ser hijo izquierdo de la raiz y la raiz el padre del nuevo nodo
 * Si no es nulo, se llama nuevamente al método con el hijo izquierdo como raíz
 * De forma igual sucede con el hijo derecho
 *
 * @param pRoot Nodo raíz o padre del nuevo nodo a insertar
 * @param pNode Nuevo nodo a insertar
 */
template<class T>
void BinaryTree<T>::insertAux(Node_BST<T> *pRoot, Node_BST<T> *pNode){

    if(pNode->getData() < pRoot->getData()){ //Caso hijo izquierdo
        if(pRoot->getHizq() == 0){
            pRoot->setHizq(pNode);
            pNode->setParent(pRoot);
            _totalNodes++;
        }
        else this->insertAux(pRoot->getHizq(), pNode);

    }

    else if(pNode->getData() > pRoot->getData()){ //Caso hijo derecho
        if(pRoot->getHder() == 0){
            pRoot->setHder(pNode);
            pNode->setParent(pRoot);
            _totalNodes++;
        }
        else this->insertAux(pRoot->getHder(), pNode);
    }

    //Caso dato duplicado
    else std::cout << MESSAGE << JUMP;

}



/**
 * @brief Método que permite obtener la raíz del árbol
 *
 * @return Nodo raíz del árbol
 */
template<class T>
Node_BST<T> *BinaryTree<T>::getRoot(){
    return this->_root;
}



/**
 * @brief Método que permite buscar un dato dentro del árbol
 *
 * Se comprueba si la raíz del árbol es nula, caso en el que se retorna
 * NULL, si no es nula se verifica si el dato que almacena es el dato
 * buscado, si lo es se retorna el nodo raíz de lo contrario de llama
 * al método auxiliar
 *
 * @see BinaryTree<T>::searchAux
 *
 * @param pData Dato que se desea buscar dentro del árbol
 * @return Nodo que contiene el dato buscado
 */
template<class T>
Node_BST<T> *BinaryTree<T>::search(const T &pData){
    if(this->_root == 0) return NULL;

    else if(this->_root->getData() == pData) return this->_root;

    else return this->searchAux(this->_root, pData);

}



/**
 * @brief Método de busqueda auxiliar
 *
 * Se comprueba si el dato buscado es menor al dato almacenado por el nodo actual (pRoot)
 * Si el dato es menor se verifica su hijo izquierdo, si el hijo izquierdo contiene el
 * dato buscado se retorna el nodo, si no se retorna NULL
 * De igual forma se verifica el hijo derecho del nodo actual (pRoot) si el dato a buscar
 * es mayor
 *
 * @param pRoot Nodo padre al cual se verifican los hijo en busca del dato
 * @param pData Dato que se busca
 *
 * @return Nodo que contiene el dato buscado
 */
template<class T>
Node_BST<T> *BinaryTree<T>::searchAux(Node_BST<T> *pRoot, const T &pData){

    if(pData < pRoot->getData()){ //Dato se encuentra en el subarbol izquierdo
        if(pRoot->getHizq() == 0) return NULL;
        else if(pRoot->getHizq()->getData() == pData) return pRoot->getHizq();
        else return this->searchAux(pRoot->getHizq(), pData);
    }

    else{ //Dato se encuentra en el subarbol derecho
        if(pRoot->getHder() == 0) return NULL;
        else if (pRoot->getHder()->getData() == pData) return pRoot->getHder();
        else return this->searchAux(pRoot->getHder(), pData);
    }
}



/**
 * @brief Método que elimina un dato dentro del árbol
 *
 * Si el árbol esta vació no se hace nada, si el dato a eliminar se encuentra en la raíz
 * se consideran los siguientes casos:
 *      ** Si solo existe la raíz dentro del arbol, se elimina la raíz
 *      ** Si hay mas de un nodo dentro del árbol, se busca el nodo mayor dentro del subarbol
 *         izquierdo de la raíz, si este es diferente a la raíz, se le asignan los
 *         los hijos y el padre de la raíz para luego eliminar la raiz.
 *         Si el nodo mayor encontrado es igual a la raíz se guarda en un nodo temporal la
 *         raíz actual y luego se actualiza si valor por el del hijo derecho, luego se
 *         elimina el nodo temporal.
 * Si el dato no se encuentra  en la raíz, se llama al método auxiliar
 *
 * @see BinaryTree::removeAux()
 *
 * @param pData Dato que se quiere eliminar del árbol
 *
 */
template<class T>
void BinaryTree<T>::remove (const T &pData){

    if(this->_root != 0){
        if(this->_root->getData() == pData){ //Dato se encuentra en la raíz
            if(this->_totalNodes == 1){ //Solo existe el nodo raíz
                delete _root;
            }
            else{ //Existen mas nodos aparte de la raíz
                Node_BST<T> *tmp = this->maxMin(this->_root);
                if(tmp != _root){
                    tmp->setHder(_root->getHder());
                    if(_root->getHder() != 0) _root->getHder()->setParent(tmp);
                    if (_root->getHizq() != tmp) tmp->setHizq(_root->getHizq());
                    if(_root->getHizq() != 0) _root->getHizq()->setParent(tmp);
                    tmp->setParent(0);
                    delete _root;
                    this->_root = tmp;
                }
                else{
                    Node_BST<T> *tmp = _root;
                    this->_root = _root->getHder();
                    delete tmp;
                }
            }
        }

        else{ //Dato no se encuentra en la raíz
            Node_BST<T> *tmp = this->search(pData);
            if(tmp != 0) this->removeAux(tmp);
        }
    }

}



/**
 * @brief Método auxiliar para remover un dato dentro del árbol
 *
 * Se comprueba si el nodo que se quiere eliminar es un nodo hoja, si lo es
 * se comprueba si es hijo izquierdo o derecho de su padre para asi asignar
 * el hijo a 0 segun sea el caso, luego se elimina el nodo
 * Si el nodo no es un nodo hoja, se busca el nodo mayor de su subarbol izquierdo
 * y se comprueban los siguientes casos:
 *      ** Si el nodo mayor es diferente al nodo a borrar, se le asignan los hijos y
 *         el padre del nodo que debe ser borrado, luego el nodo se borra
 *      ** Si el nodo mayor es igual al nodo a borrar, significa que este no tiene
 *         subarbol izquierdo, por lo que a su padre se le asigna como hijo izquierdo
 *         o derecho (segun sea el caso), el hijo derecho del nodo a borrar.
 *
 * @param pNode Nodo que debe ser borrado dentro del árbol
 */
template<class T>
void BinaryTree<T>::removeAux(Node_BST<T> *pNode){
    if(!pNode->hasHizq() && !pNode->hasHder()){ //Nodo a borrar es un nodo hoja

        if(pNode->getParent()->getHizq() == pNode) pNode->getParent()->setHizq(0);
        else pNode->getParent()->setHder(0);
        delete pNode;
    }

    else{ //Nodo a borrar no es nodo hoja
        Node_BST<T> *tmp = this->maxMin(pNode);
        if(tmp != pNode){ //Nodo a borrar tiene subarbol izquierdo
            tmp->setHder(pNode->getHder());
            if(pNode->getHder() != 0) pNode->getHder()->setParent(tmp);
            if(pNode->getHizq() != 0){
                tmp->setHizq(pNode->getHizq());
                pNode->getHizq()->setParent(tmp);
            }
            tmp->setParent(pNode->getParent());
            if(pNode->getParent()->getHizq() == pNode) pNode->getParent()->setHizq(tmp);
            else pNode->getParent()->setHder(tmp);
            delete pNode;
        }

        else{ //Nodo a borrar no tiene subarbol izquierdo
            if(tmp->getParent()->getHizq() == tmp) tmp->getParent()->setHizq(tmp->getHder());
            else tmp->getParent()->setHder(tmp->getHder());
            tmp->getHder()->setParent(tmp->getParent());
            delete tmp;
        }
    }
}



/**
 * @brief Método que retornar el nodo mayor del subarbol izquierdo del nodo enviado como parametro
 *
 * Si el nodo parametro tiene hijo izquierdo, se recorre iterativamente su subarbol derecho
 * hasta encontrar el ultimo nodo, el cual es el mayor de los menores.
 * Si el nodo parametro no tiene hijo izquierdo se retorna NULL
 *
 * @param pNode Nodo padre del subarbol izquierdo al cual se quiere encontrar el nodo mayor
 *
 * @return Nodo mayor del subarbol izquierdo
 */
template<class T>
Node_BST<T> *BinaryTree<T>::maxMin(Node_BST<T> *pNode){
    if(pNode->getHizq() != 0){
        Node_BST<T> *tmp = pNode->getHizq();
        while(tmp->getHder() != 0){
            tmp = tmp->getHder();
        }
        if(tmp->getParent()->getHizq() == tmp) tmp->getParent()->setHizq(0);
        else tmp->getParent()->setHder(0);
        return tmp;
    }
    else return pNode;
}



/**
 * Método que retorna la cantidad de nodos existentes dentro del árbol
 */
template<class T>
int BinaryTree<T>::getTotalNodes(){
    return this->_totalNodes;
}


/**
 * @brief Método para imprimir los datos por niveles del árbol
 *
 * Se crea una cola donde se encolaran los nodos del árbol
 * Se comprueba si el árbol esta vacio, si lo esta no hace nada
 * Si el árbol no esta vacío, se encola la raíz del árbol y se
 * llama al método auxiliar
 *
 * @see BinaryTree::printAux()
 */
template<class T>
void BinaryTree<T>::print(){
    Queue< Node_BST<T> > *queue = new Queue< Node_BST<T> >();

    if(this->_root == 0) return;
    else{
        queue->enqueue(*this->_root);
        this->printAux(queue);
    }
}


/**
 * @brief Método para imprimir auxiliar
 *
 * De manera iterativa, mientras lo cola no este vacía, se des encola
 * un nodo de la cola y se imprime su dato, luego se comprueba si tiene
 * hijo izquierdo o hijo derecho y se encolan. De este  modo se imprimen
 * los datos del árbol por niveles
 *
 * @param pQueue Cola donde se almacenan los nodos
 */
template<class T>
void BinaryTree<T>::printAux(Queue<Node_BST<T> > *pQueue){

    while(!pQueue->isEmpty()){
        Node_BST<T> tmp = pQueue->dequeue()->getData();
        std::cout << tmp.getData() << JUMP;
        if(tmp.hasHizq()) pQueue->enqueue(*tmp.getHizq());
        if(tmp.hasHder()) pQueue->enqueue(*tmp.getHder());
    }
}



/*
template<class T>
static bool operator<(const T& p1, const T& p2){
    return (&p1 < &p2);
}

template<class T>
static bool operator>(const T& p1, const T& p2){
    return (&p1 > &p2);
}
*/



