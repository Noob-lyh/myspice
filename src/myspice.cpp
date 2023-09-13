#include<stdio.h>
#include"myspice.h"

int main(int argc, char** argv){

    printf("----- myspice v0.0 by lyh -----\n");

    int myspice_stat = 0;

    int iparm[64] = {0};
    double dparm[64] = {0};
    char *netlist_name = NULL;
    myspice_stat = argparse(argc, argv, iparm, dparm, netlist_name);

    mynetlist net;
    myspice_stat = read_netlist(netlist_name, net);


    return myspice_stat;
}