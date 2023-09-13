#ifndef __MYSPICE__
#define __MYSPICE__

#include<stdio.h>



// defines
#define MYSPICE_SUCCESS             (0)
#define MYSPICE_ARGUMENT_ERROR      (-1)
#define MYSPICE_FILE_CANNOT_OPEN    (-2)
#define MYSPICE_FILE_FORMAT_ERROR   (-3)


// structures
typedef struct mynetlist
{
    int nodes;
};



// funtions
void help_message()
{
    printf("Help message.\n");
    return;
}

int argparse(int, char**, int*, double*, char*);

int read_netlist(char*, mynetlist&);

#endif