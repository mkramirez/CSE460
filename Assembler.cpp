//
// Created by Matthew Ramirez on 9/25/18.
//

#include "Assembler.h"
#include <iomanip>
#include <sstream>
#include <iostream>

Assembler::Assembler() {
    jumpTable["load"] = &Assembler::load;
    jumpTable["loadi"] = &Assembler::loadi;
    jumpTable["store"] = &Assembler::store;
    jumpTable["add"] = &Assembler::add;
    jumpTable["addi"] = &Assembler::addi;
    jumpTable["addc"] = &Assembler::addc;
    jumpTable["addci"] = &Assembler::addci;
    jumpTable["sub"] = &Assembler::sub;
    jumpTable["subi"] = &Assembler::subi;
    jumpTable["subc"] = &Assembler::subc;
    jumpTable["subci"] = &Assembler::subci;
    jumpTable["_and"] = &Assembler::_and;
    jumpTable["andi"] = &Assembler::andi;
    jumpTable["_xor"] = &Assembler::_xor;
    jumpTable["xori"] = &Assembler::xori;
    jumpTable["_compl"] = &Assembler::_compl;
    jumpTable["shl"] = &Assembler::shl;
    jumpTable["shla"] = &Assembler::shla;
    jumpTable["shr"] = &Assembler::shr;
    jumpTable["shra"] = &Assembler::shra;
    jumpTable["compr"] = &Assembler::compr;
    jumpTable["compri"] = &Assembler::compri;
    jumpTable["getstat"] = &Assembler::getstat;
    jumpTable["putstat"] = &Assembler::putstat;
    jumpTable["jump"] = &Assembler::jump;
    jumpTable["jumpl"] = &Assembler::jumpl;
    jumpTable["jumpe"] = &Assembler::jumpe;
    jumpTable["jumpg"] = &Assembler::jumpg;
    jumpTable["call"] = &Assembler::call;
    jumpTable["_return"] = &Assembler::_return;
    jumpTable["read"] = &Assembler::read;
    jumpTable["write"] = &Assembler::write;
    jumpTable["halt"] = &Assembler::halt;
    jumpTable["noop"] = &Assembler::noop;
}

int Assembler::assemble(std::fstream & in, std::fstream & out) {
    std::string line;
    std::string opcode;
    const int success = false;
    const int error = true;
    //const int debug = false;
    int instruction;

    getline(in, line);
    while (!in.eof()) {
        std::istringstream str(line.c_str());
        str >> opcode;
        if (opcode[0] == '!') {
            getline(in, line);
            continue;
        }

        try {
            if (not jumpTable[opcode] )
                throw NullPointerException();
            else instruction = (this->*jumpTable[opcode])(str);

        } catch (NullPointerException e) {
            std::cerr << e.what() << std::endl;
            return error;
        }

        if (instruction == -1)
            return error;
        out << instruction << std::endl;
        getline(in, line);
    }
    return success;
}

int Assembler::load(std::istringstream & str) {
    int rd, addr;
    str >> rd >> addr;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 0;
    inst = inst | rd << 9 | addr;
    return inst;
}

int Assembler::loadi(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 0;
    inst = inst | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::store(std::istringstream & str) {
    int rd, addr;
    str >> rd >> addr;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 1;
    inst = inst << 11 | rd << 9 | 1 << 8 | addr;
    return inst;
}

int Assembler::add(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 2;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int Assembler::addi(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 2;
    inst = inst << 11 || rd << 9 | 1 << 8 || (0x000000ff & constant);
    return inst;
}

int Assembler::addc(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 3;
    inst = inst << 11 || rd << 9 | rs << 6;
    return inst;
}

int Assembler::addci(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 3;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::sub(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 0) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 4;
    inst = inst << 11 || rd << 9 | rs << 6;
    return inst;
}

int Assembler::subi(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 0) {
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 4;
    inst = inst << 11 || rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::subc(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 5;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int Assembler::subci(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 5;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;

}

int Assembler::_and(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 6;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int Assembler::andi(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (constant < -128 || constant > 127) {
        return -1;
    }
    int inst = 6;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::_xor(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 7;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int Assembler::xori(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 7;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::_compl(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 8;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shl(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 9;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shla(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 10;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shr(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 11;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::shra(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 12;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::compr(std::istringstream & str) {
    int rd, rs;
    str >> rd >> rs;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    if (rs < 0 || rs > 3) {
        return -1;
    }
    int inst = 13;
    inst = inst << 11 | rd << 9 | rs << 6;
    return inst;
}

int Assembler::compri(std::istringstream & str) {
    int rd, constant;
    str >> rd >> constant;
    if (rd < 0 || rd > 3){
        return -1;
    }
    if (constant < -128 || constant > 127){
        return -1;
    }
    int inst = 13;
    inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
    return inst;
}

int Assembler::getstat(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 14;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::putstat(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 15;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::jump(std::istringstream & str) {
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 16;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::jumpl(std::istringstream & str) {
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 17;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::jumpe(std::istringstream & str) {
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 18;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::jumpg(std::istringstream & str) {
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 19;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::call(std::istringstream & str) {
    int addr;
    str >> addr;
    if (addr < 0 || addr > 255) {
        return -1;
    }
    int inst = 20;
    inst = inst << 11 | 1 << 8 | addr;
    return inst;
}

int Assembler::_return(std::istringstream & str) {
    int inst = 21;
    inst = inst << 11;
    return inst;
}

int Assembler::read(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 22;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::write(std::istringstream & str) {
    int rd;
    str >> rd;
    if (rd < 0 || rd > 3) {
        return -1;
    }
    int inst = 23;
    inst = inst << 11 | rd << 9;
    return inst;
}

int Assembler::halt(std::istringstream & str) {
    int inst = 24;
    inst = inst << 11;
    return inst;
}

int Assembler::noop(std::istringstream & str) {
    int inst = 25;
    inst = inst << 11;
    return inst;
}
