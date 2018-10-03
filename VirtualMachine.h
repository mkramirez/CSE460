#ifndef PHASE_1_VIRTUALMACHINE_H
#define PHASE_1_VIRTUALMACHINE_H

#include <vector>

class VirtualMachine {
    static const int REG_FILE_SIZE = 4;
    static const int MEM_SIZE = 256;
    std::vector <int> r;
    std::vector <int> mem;
    int pc;
    int ir;
    int sr;
    int sp;
    int clock;
    int base;
    int limit;

public:
    VirtualMachine(): clock(0) {
        mem.reserve(MEM_SIZE);
        r.reserve(REG_FILE_SIZE);
    }
    void run(std::fstream&, std::fstream&, std::fstream&);
    int get_clock();

private:
    void carryBit();
    void greaterBit();
    void equalBit();
    void lessBit();
    void overflowBit();
    void clearBit();

    void load();
    void loadi();
    void store();
    void add();
    void addi();
    void addc();
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