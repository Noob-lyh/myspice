#include"myspice.h"
#include"string.h"

void help_message(){

    printf("Options:\n");
    printf("-f [input_file]\n");
    printf("-p [phase]\n");
    return;

};

int argparse(int argc, char** argv, int* iparm, double* dparm, char* input_file){

    if (argc < 3)
        return MYSPICE_ARGUMENT_ERROR;

    for (int i = 1; i < argc;) {

        if (strcmp(argv[i], "-f") == 0) {
            if(i+1 > argc)
                return MYSPICE_ARGUMENT_ERROR;
            input_file = argv[i+1];
            i += 2;
        }

        else if (strcmp(argv[i], "-p") == 0) {
           if(i+1 > argc)
                return MYSPICE_ARGUMENT_ERROR;
            iparm[0] = atoi(argv[i+1]);
            i += 2;
        } 

    }

    if (input_file == NULL)
        return MYSPICE_NO_INPUT_FILE;
    else
        return MYSPICE_SUCCESS;
};