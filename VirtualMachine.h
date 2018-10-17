/*
 * The virtual machine header is built here with the use of the contructors being created
 * as well as creating a function to get the clock timer and run the VM
 */
#ifndef PHASE_1_VIRTUALMACHINE_H
#define PHASE_1_VIRTUALMACHINE_H

#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class VirtualMachine { //all of the class constructors for VM
    int msize;
    int rsize;
    std::vector<int> r;
    std::vector<int> mem;
    int pc;
    int ir;
    int sr;
    int sp;
    int clock;
    int base;
    int limit;

public:
    VirtualMachine() : msize(256), rsize(4), clock(0) {
        mem.reserve(msize); r.reserve(rsize);
    }
    void run(std::fstream &, std::fstream &, std::fstream &);

    int get_clock();

};
#endif //PHASE_1_VIRTUALMACHINE_H