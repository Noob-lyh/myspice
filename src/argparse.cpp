#include"myspice.h"

void help_message(){

    printf("Options:\n");
    printf("-h, help message.\n");
    printf("-f [input_file], set input file.\n");
    printf("-p [phase], set work phase.\n");
    return;

};

int argparse(int argc, char** argv, int* iparm, double* dparm, char** input_file){

    for (int i = 1; i < argc;) {

        if (strcmp(argv[i], "-f") == 0) {
            if(i+1 > argc)
                return MYSPICE_ARGUMENT_ERROR;
            *input_file = argv[i+1];
            i += 2;
        }

        else if (strcmp(argv[i], "-p") == 0) {
           if(i+1 > argc)
                return MYSPICE_ARGUMENT_ERROR;
            iparm[0] = atoi(argv[i+1]);
            i += 2;
        } 

        else if (strcmp(argv[i], "-h") == 0) {
           help_message();
           i++;
        } 

        else {
            return MYSPICE_ARGUMENT_ERROR;
        }

    }

    if (input_file == NULL)
        return MYSPICE_NO_INPUT_FILE;
    else
        return MYSPICE_SUCCESS;
};