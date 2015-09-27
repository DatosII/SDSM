#include "SDSMMemoryNode/SDSMMemoryNode.h"

int main(){

    SDSMMemoryNode *node = new SDSMMemoryNode(2,'M',6000,6005);

    std::cout << "MEMORIA TOTAL: " << node->_totalMem << "\n";
    std::cout << "INICIO DE MEMORIA: " << node->_initDirection << "\n";


    unsigned char array[] = "d_calloc:0000002d";
    unsigned char *stream = array;

    unsigned char array2[] = "d_calloc:00000050";
    unsigned char *stream2 = array2;

    unsigned char *value1 = node->parser(stream);
    unsigned char *value2 = node->parser(stream2);



//    std::printf("%x\n", value1[1]);
//    std::printf("%x\n", value1[2]);
//    std::printf("%x\n", value1[3]);
//    std::printf("%x\n", value1[4]);

   // std::cout << value[0] << "\n";




    
    return 0;
}
