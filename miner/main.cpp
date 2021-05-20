

#include <libethash-fpga/FPGAMiner.h>


int main(int argc, char** argv)
{

    printf("\n\n");


    Miner m; 

    m.init();
    m.workLoop();

    return 0;
}