//#include <linkedlist.h>

///**
//* @brief Constructor que inicializa los punteros al head y el tail como nulos
//*/

//LinkedList::LinkedList(void* pPunteroDHeap): _head(0), _tail(0)
//{
//    punterodHeap = pPunteroDHeap;
//}



///**
//* @brief Método que permite insertar un nuevo dato en la lista
//*
//* @param pData Dato que se quiere insertar dentro de la lista
//*/
//void LinkedList::insert(const string &pData1,const string &pData2) {

//    Node_LL *newNode = new Node_LL(pData1, pData2, punterodHeap);

//    if (_head == 0){
//        _head = _tail = newNode;
//    }
//    else{
//        Node_LL *tmp = _head;
//        while((*tmp).getNext() != 0){
//            tmp = tmp->getNext();
//        }
//        tmp->setNext(newNode);
//        _tail = tmp;
//    }
//}



///**
//* @brief Método que elimina un dato dentro de la lista
//*
//* Recorre la lista comparando el dato almacenado por cada nodo
//* con el dato que se quiere eliminar, cuando se encuentra el
//* nodo que almacena el dato, este es eliminado
//*
//* @param pData Dato que se quiere borrar de la lista
//*/
//void LinkedList::remove(const string &pData1){
//    if(_head == 0){ //Lista esta vacia
//        return;
//    }
//    else if(_head->getData() == pData1){ //Dato se encuentra en el head
//        Node_LL *temp = _head;
//        _head = _head->getNext();
//        delete temp;
//    }
//    else{ //Dato no esta en el head, se debe buscar
//        Node_LL *prev = _head, *next = _head->getNext();
//        while(next != 0){
//            if(next->getData() == pData1){
//                prev->setNext(next->getNext());

//                if(next == _tail){
//                    _tail = prev;
//                }
//                delete next;
//                break;
//            }

//            prev = next;
//            next = next->getNext();
//        }
//    }
//}


///**
//* @brief Método que busca un dato dentro de la lista
//*
//* Recorre la lista comparando el dato almacenado en cada nodo
//* con el dato que se busca, si se encuentra el nodo que contiene
//* el dato, este se retorna; en caso constrario se retorna NULL
//*
//* @param pData Dato que se quiere buscar dentro de la lista
//*
//* @return Nodo que contiene el dato buscado
//*/
//Node_LL *LinkedList::find(string pData1){
//    if(_head != 0){
//        Node_LL *temp = _head;
//        while(temp != 0){
//            if(temp->getData() == pData1){
//                return temp;
//            }
//            temp = temp->getNext();
//        }
//    }
//    else{
//        std::cout << MESSAGE << JUMP;
//        return NULL;
//    }
//}



///**
//* @brief Método que retorna el head de la lista
//*
//* @return Head de la lista
//*/
//Node_LL *LinkedList::getHead() {
//    return this->_head;
//}


///**
//* @brief Método que imprime todos los datos almacenados dentro de la lista
//*/
//void LinkedList::print(){
//    Node_LL *tmp = _head;
//    while(tmp != 0){
//        std::cout << tmp->getData() << JUMP;
//        tmp = tmp->getNext();
//    }
//}


///**
//* @brief Destructor de la clase
//*
//* Recorre toda la lista borrando los punteros a cada nodo
//*/
//LinkedList::~LinkedList(){
//    if(_head != 0){
//        Node_LL *current = _head;
//        Node_LL *next;

//        while(current->getNext() != 0){
//            next = current->getNext();
//            delete current;
//            current = next;
//        }
//    }
//}
