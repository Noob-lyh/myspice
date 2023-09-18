#include"myspice.h"
#include"string.h"

void help_message(){

    printf("help_message.\n");

    return;

};

int argparse(int argc, char** argv, int* iparm, double* dparm, char* netlist_name){

    if (argc < 3)
        return MYSPICE_ARGUMENT_ERROR;

    for (int i = 1; i < argc;) {

        if (strcmp(argv[i], "-f") == 0) {
            if(i+1 > argc)
                return MYSPICE_ARGUMENT_ERROR;
            netlist_name = argv[i+1];
            i += 2;
        }

        else if (strcmp(argv[i], "-0") == 0) {
            iparm[0] = 0;
        } 

    }

    return MYSPICE_SUCCESS;
};