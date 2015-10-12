#include "SDSMMemoryNode/SDSMMemoryNode.h"
#include "SDSMMemoryNode/servidorsmsmm.h"

int main(){

	unsigned short port = 6000;
	unsigned short state = 6005;
	//SDSMMemoryNode *node = new SDSMMemoryNode(4,'M', "192.168.1.3", port, state);

	ServidorSMSMM *server = new ServidorSMSMM(1, 'M', "192.168.1.3", port, state);



//	std::cout << "MEMORIA TOTAL: " << node->_totalMem << "\n";
//	std::cout << "INICIO DE MEMORIA: " << node->_initDirection << "\n";


//	unsigned char array[] = ">>>>>";
//	unsigned char *stream = array;

	std::cout << "################D_CALLOC####################" << "\n";

//	unsigned char array2[] = "645f63616c6c6f633a04000000";
//	unsigned char *stream2 = array2;

//	unsigned char array3[] = "645f63616c6c6f633a83070000";
//	unsigned char *stream3 = array3;

//	unsigned char *value1 = node->parser(stream2);
//	delete value1;

//	unsigned char *value2 = node->parser(stream2);
//	delete value2;

//	unsigned char *value3 = node->parser(stream3);
//	delete value3;



//	node->_memoryList->print();

//	std::cout << "################D_SET####################" << "\n";

//	unsigned char array4[] = "645f7365743ac1a803017017000000000400000045789421";
//	unsigned char *stream4 = array4;

//	unsigned char *value4 = node->parser(stream4);


//	unsigned int *total = (unsigned int*)value4;
//	unsigned char *offset = value4+4;
//	unsigned int *use = (unsigned int*)offset;

//	std::cout << "TOTAL: " << *total << "  " << "USED: " << *use << "\n";




	/*std*/::cout << "################D_GET####################" << "\n";

//	unsigned char array5[] = "645f6765743ac0a8010370170000000004000000";
//	unsigned char *stream5 = array5;

//	unsigned char *value5 = node->parser(stream5);

//	for(int i = 0; i< 5; i++){
//		std::printf("%x\n", value5[i]);
//	}


//	node->_memoryList->print();


//	std::cout << "################D_FREE####################" << "\n";

//	unsigned char array5[] = "645f667265653ac0a8010370172d0000002d000000";
//	unsigned char *stream5 = array5;
//	unsigned char *value5 = node->parser(stream5);


//	node->_memoryList->print();

    
    return 0;
}
