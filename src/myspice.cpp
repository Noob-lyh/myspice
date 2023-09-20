#include"myspice.h"

#define CHECK_STAT(stat) if(stat!=MYSPICE_SUCCESS) goto RET

int main(int argc, char** argv){

    printf("----- myspice v0.0 by lyh -----\n");

    int myspice_stat = 0;
    int iparm[64] = {0};
    double dparm[64] = {0};
    char *input_file = NULL;
    string input_file_prefix;
    Stamp s;

    // default setting
    iparm[0] = 1;           // phase: 0-nothing, 1-stamp

    // argparse
    myspice_stat = argparse(argc, argv, iparm, dparm, &input_file);
    CHECK_STAT(myspice_stat);
    printf("input file = %s\n", input_file);
    int i; for(i = strlen(input_file)-1; i > 0 && input_file[i] != '.'; --i); input_file_prefix = string(input_file, i);

    // works
    if(iparm[0] == 1){
        printf("stamping...\n");
        printf("  parsing netlist...\n");
        s.parse(input_file);
        printf("  setting up matrixes...\n");
        s.setup();
        printf("  writing result...\n");
        string output_file = input_file_prefix + ".out";
        s.output(output_file.c_str());
    }

RET:
    printf("return code = %d\n", myspice_stat);
    return myspice_stat;
}