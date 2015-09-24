#ifndef MEMORYLIST
#define MEMORYLIST

#include "Structures/Nodes/memorynode.h"

#define JUMP "\n"
#define MESSAGE "NO ENCONTRE EL DATO"

/**
 * @file memorylist.h
 * @brief Crea una lista doblemente enlazada
 * con un método de insertar en orden
 * @author Juan Pablo Brenes
 * @date 23/9/2015
 */

    class  MemoryList {

        public:
            MemoryList(unsigned int pInitMem, unsigned int pTotalMem); //Constructor
            ~MemoryList(); //Destructor
            MemoryNode* getHead(); //Método para obtener el head
            unsigned int getTotalNodes(); //Método para obtener la cantidad de nodos dentro de la lista
            unsigned int* insert(MemoryNode *pNode); //Método para insertar un dato
            void remove(); //Método para eliminar un dato
            MemoryNode* find(std::string pID, unsigned int pMemAddress); //Método para buscar un dato
            void print(); //Método para imprimir toda la lista

        private:
            unsigned int* insertAux(MemoryNode *pNode); //Método auxiliar para insertar un dato

            MemoryNode *_head;
            MemoryNode *_tail;
            unsigned int _initMem, _totalMem;
            unsigned int _totalNodes;
    };

#endif // MEMORYLIST

