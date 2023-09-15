#include"myspice.h"
#include<string.h>
#include<ctype.h>

#define MAX_LINE_LENGTH 1024

int read_netlist(char* netlist_name, mynetlist& net){

    // initialize


    // read
    FILE *f;
    if ((f = fopen(netlist_name, "r")) == NULL)
        return MYSPICE_FILE_CANNOT_OPEN;

    char line[MAX_LINE_LENGTH];
    do{

        if (fgets(line,MAX_LINE_LENGTH,f) == NULL)
            return MYSPICE_FILE_FORMAT_ERROR;

        switch (line[0]){

        case '*':
        continue;

        case '.':
            char *tmp = strtok(line," ");
            tmp = strlwr(tmp);
            if(strcmp(tmp,".end"))
                break;

            while(tmp)
            {
                printf("%s\n",tmp);
                tmp = strtok(NULL," ");
            }
            
        break;

        }

    }while (1);

    

    return MYSPICE_SUCCESS;
};