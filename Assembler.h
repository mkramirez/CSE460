#ifndef PHASE_1_ASSEMBLER_H
#define PHASE_1_ASSEMBLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>

class NullPointerException: public std::runtime_error {
public:
    NullPointerException(): runtime_error("Null Function Pointer!") { }
};

class Assembler {
public:
    typedef int (Assembler::*FP)(std::istringstream &); //function pointer
    std::map<std::string, FP> jumpTable;
    Assembler();//constructor


    int assemble(std::fstream&, std::fstream&);

private:
    int load(std::istringstream &);
    int loadi(std::istringstream &);
    int store(std::istringstream &);
    int add(std::istringstream &);
    int addi(std::istringstream &);
    int addc(std::istringstream &);
    int addci(std::istringstream &);
    int sub(std::istringstream &);
    int subi(std::istringstream &);
    int subc(std::istringstream &);
    int subci(std::istringstream &);
    int ㅅand(std::istringstream &);
    int andi(std::istringstream &);
    int ㅅxor(std::istringstream &);
    int xori(std::istringstream &);
    int ㅅcompl(std::istringstream &);
    int shl(std::istringstream &);
    int shla(std::istringstream &);
    int shr(std::istringstream &);
    int shra(std::istringstream &);
    int compr(std::istringstream &);
    int compri(std::istringstream &);
    int getstat(std::istringstream &);
    int putstat(std::istringstream &);
    int jump(std::istringstream &);
    int jumpl(std::istringstream &);
    int jumpe(std::istringstream &);
    int jumpg(std::istringstream &);
    int call(std::istringstream &);
    int ㅅreturn(std::istringstream &);
    int read(std::istringstream &);
    int write(std::istringstream &);
    int halt(std::istringstream &);
    int noop(std::istringstream &);
};

#endif //PHASE_1_ASSEMBLER_H
