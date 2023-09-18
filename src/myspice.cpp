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
    iparm[0] = 0;           // phase: 0-nothing, 1-stamp

    // argparse
    myspice_stat = argparse(argc, argv, iparm, dparm, input_file);
    CHECK_STAT(myspice_stat);
    int i;
    for(i = strlen(input_file)-1; i > 0 && input_file[i] != '.'; --i);
    input_file_prefix = string(input_file, i);

    // works
    if(iparm[0] == 1){
        s.parse(input_file);    // A.sp -> class member
        s.setup();              // class member -> matrix
        string output_file = input_file_prefix + ".out";
        s.output(output_file.c_str());      // matrix -> output file
    }

RET:
    return myspice_stat;
}