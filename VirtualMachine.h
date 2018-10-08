
#ifndef PHASE_1_VIRTUALMACHINE_H
#define PHASE_1_VIRTUALMACHINE_H

#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>
#include "iostream"

class VirtualMachine {
    typedef void (VirtualMachine::*FP)();
    int msize;
    int rsize;
    std::vector <int> r;
    std::vector <int> mem;
    int pc;
    int ir;
    int sr;
    int sp;
    int clock;
    int base;
    int limit;
    std::map<int, FP> instr;

public:
    VirtualMachine(): msize(256), rsize(4), clock(0) { mem.reserve(msize); r.reserve(rsize); }
    void run(std::fstream&, std::fstream&, std::fstream&);
    int get_clock();

private:
    void load();
    void loadi();
    void store();
    void add();
    void addi();
    void addc();
    void addci();
    void sub();
    void subi();
    void subc();
    void subci();
    void ㅅand();
    void andi();
    void ㅅxor();
    void xori();
    void ㅅcompl();
    void shl();
    void shla();
    void shr();
    void shra();
    void compr();
    void compri();
    void getstat();
    void putstat();
    void jump();
    void jumpl();
    void jumpe();
    void jumpg();
    void call();
    void ㅅreturn();
    void read();
    void write();
    void halt();
    void noop();
};

class format_1{};

class format_2{};

class format_3{};

#endif //PHASE_1_VIRTUALMACHINE_H