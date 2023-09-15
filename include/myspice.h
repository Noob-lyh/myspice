#ifndef __MYSPICE_H__
#define __MYSPICE_H__

#include<stdio.h>



// defines
#define MYSPICE_SUCCESS             (0)
#define MYSPICE_ARGUMENT_ERROR      (-1)
#define MYSPICE_FILE_CANNOT_OPEN    (-2)
#define MYSPICE_FILE_FORMAT_ERROR   (-3)


// structures
struct mynetlist
{
    int nodes;
};



// funtions
void help_message();

int argparse(int, char**, int*, double*, char*);

int read_netlist(char*, mynetlist&);

#endif