#include "SDSMMemoryNode/SDSMMemoryNode.h"
#include "SDSMMemoryNode/servidorsmsmm.h"

int main(){

	unsigned short port = 8200;
	unsigned short state = 6005;
	//SDSMMemoryNode *node = new SDSMMemoryNode(4,'M', "192.168.1.3", port, state);

	ServidorSMSMM *server = new ServidorSMSMM(4, 'M', "192.168.1.3", port, state);


//    std::cout << "MEMORIA TOTAL: " << node->_totalMem << "\n";
//    std::cout << "INICIO DE MEMORIA: " << node->_initDirection << "\n";


//	unsigned char array[] = "645f63616c6c6f633a2d000000";
//    unsigned char *stream = array;

//	unsigned char array2[] = "645f63616c6c6f633a50000000";
//	unsigned char *stream2 = array2;

//	unsigned char array3[] = "645f63616c6c6f633a83070000";
//	unsigned char *stream3 = array3;

//	unsigned char *value1 = node->parser(stream);
//	delete value1;

//	unsigned char *value2 = node->parser(stream2);
//	delete value2;

//	unsigned char *value3 = node->parser(stream3);
//	delete value3;



//	node->_memoryList->print();

//	std::cout << "################D_SET####################" << "\n";

//	unsigned char array4[] = "645f7374617475733a";
//	unsigned char *stream4 = array4;

//	unsigned char *value4 = node->parser(stream4);


//	unsigned int *total = (unsigned int*)value4;
//	unsigned char *offset = value4+4;
//	unsigned int *use = (unsigned int*)offset;

//	std::cout << "TOTAL: " << *total << "  " << "USED: " << *use << "\n";




//	std::cout << "################D_GET####################" << "\n";

//	unsigned char array5[] = "d_get:c0a8010370172d00000003000000";
//	unsigned char *stream5 = array5;

//	unsigned char *value5 = node->parser(stream5);

//	for(int i = 0; i< 4; i++){
//		std::printf("%x\n", value5[i]);
//	}


//	node->_memoryList->print();


//	std::cout << "################D_FREE####################" << "\n";

//	unsigned char array5[] = "d_free:c0a8010370172d00000009000000";
//	unsigned char *stream5 = array5;
//	unsigned char *value5 = node->parser(stream5);


//	node->_memoryList->print();

    
    return 0;
}
