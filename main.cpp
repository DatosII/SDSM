#include "SDSMMemoryNode/SDSMMemoryNode.h"
#include "SDSMMemoryNode/servidorsmsmm.h"

int main(){

	unsigned short port = 6000;
	unsigned short state = 6005;
	//SDSMMemoryNode *node = new SDSMMemoryNode(4,'M', "192.168.1.3", port, state);

	ServidorSMSMM *server = new ServidorSMSMM(1, 'M', "192.168.1.3", port, state);



    
    return 0;
}
