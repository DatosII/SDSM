//#include "linkedlistmd.h"


///**
//* @brief Constructor que inicializa los punteros al head y el tail como nulos
//* Inicia las operaciones del garbajeCollector en la lista de metadatos.
//*/

//LinkedListMD::LinkedListMD(void* pPunteroDHeap, int pFrecuencia): _head(0), _tail(0)
//{
//    punterodHeap = pPunteroDHeap;
//    parametros = new parametrosGarbaje();

//    parametros->frecuencia = pFrecuencia;
//    parametros->listaMetadatos = this;
//    parametros->pPunteroDHeap = punterodHeap;

//    pthread_create(&hiloGarbaje,NULL,garbajeCollector,parametros);
//}



///**
//* @brief Método que permite insertar un nuevo dato en la lista
//*
//* @param pData Dato que se quiere insertar dentro de la lista
//*/
//void LinkedListMD::insert(d_pointer_size_type pPointer) {

//    Node_MD *newNode = new Node_MD(pPointer);

//    if (_head == 0){
//        _head = _tail = newNode;
//    }
//    else{
//        Node_MD *tmp = _head;
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
//void LinkedListMD::remove(d_pointer_size_type pPointer){
//    if(_head == 0){ //Lista esta vacia
//        return;
//    }
//    else if(*(_head->getData()) == pPointer){ //Dato se encuentra en el head
//        Node_MD *temp = _head;
//        _head = _head->getNext();
//        delete temp;
//    }
//    else{ //Dato no esta en el head, se debe buscar
//        Node_MD *prev = _head, *next = _head->getNext();
//        while(next != 0){
//            if(*(next->getData()) == pPointer){
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
//Node_MD *LinkedListMD::find(d_pointer_size_type pPointer){
//    if(_head != 0){
//        Node_MD *temp = _head;
//        while(temp != 0){
//            if(*(temp->getData()) == pPointer){
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
//Node_MD *LinkedListMD::getHead() {
//    return this->_head;
//}


///**
//* @brief Método que imprime todos los datos almacenados dentro de la lista
//*/
//void LinkedListMD::print(){
//    Node_MD *tmp = _head;
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
//LinkedListMD::~LinkedListMD(){
//    if(_head != 0){
//        Node_MD *current = _head;
//        Node_MD *next;

//        while(current->getNext() != 0){
//            next = current->getNext();
//            delete current;
//            current = next;
//        }
//    }
//}

///**
// * @brief LinkedListMD::garbajeCollector hilo que
// * revisa las referencias de los metadatos para
// * conocer si se tienen que eliminar automaticamente o no.
// * @param pParametros
// */
//void* LinkedListMD::garbajeCollector(void *pParametros){
//    int _inicio = 0;
//    int _final = 0;
//    _inicio = _final = time(NULL);
//    while(true){
//        while(_final-_inicio < ((parametrosGarbaje*)pParametros)->frecuencia){
//            _final = time(NULL);
//        }
//        Node_MD* _temp= ((LinkedListMD*)((parametrosGarbaje*)pParametros)->listaMetadatos)->getHead();
//        while(_temp != NULL){
//            //Seccion en la que se revisa el contador de referencias de los d_pointerSize
//            //no se ha podido realizar porque falta agregar la configuracion del
//            //d_pointer_size_type.
//        }
//    }
//}
