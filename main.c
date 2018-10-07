#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"





int main(int argc, char *argv[])
{   Retea *network;
   

    network=Network_Creation(argv[1]);
  	//si_verification(network,argv[2],0);
  	//up_pc(&network,0);
	//broke_pc(&network,0);
	//lc_operation(&network,0);
	//add_operation(&network,0);
	//ping(network,argv[2],0);
	//trace_operation(network,argv[2],1);
    execution(network,argv[2]);
    printf("\n%s    %s   \n",(network)->Conexiune[(network)->nr_conexiuni_routere-1].nume_router_start,(network)->Conexiune[(network)->nr_conexiuni_routere-1].nume_router_finish);

	return 0;
}