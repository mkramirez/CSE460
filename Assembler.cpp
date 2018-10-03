//
// Created by Matthew Ramirez on 9/25/18.
//

#include "Assembler.h"

Assembler::Assembler() {
    jumpTable["load"] = &Assembler::load;
    jumpTable["loadi"] = &Assembler::loadi;
    jumpTable["store"] = &Assembler::store;
    jumpTable["add"] = &Assembler::add;
    jumpTable["addi"] = &Assembler::addi;
    jumpTable["addc"] = &Assembler::addc;
    jumpTable["sub"] = &Assembler::sub;
    jumpTable["subi"] = &Assembler::subi;
    jumpTable["subc"] = &Assembler::subc;
    jumpTable["subci"] = &Assembler::subci;
    jumpTable["ㅅand"] = &Assembler::ㅅand;
    jumpTable["andi"] = &Assembler::andi;
    jumpTable["ㅅxor"] = &Assembler::ㅅxor;
    jumpTable["xori"] = &Assembler::xori;
    jumpTable["ㅅcompl"] = &Assembler::ㅅcompl;
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
    jumpTable["ㅅreturn"] = &Assembler::ㅅreturn;
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
    inst = inst << 11 | rd << 9 | addr;
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

int Assembler::addi(std::istringstream &) {
    return 0;
}

int Assembler::addc(std::istringstream &) {
    return 0;
}

int Assembler::sub(std::istringstream &) {
    return 0;
}

int Assembler::subi(std::istringstream &) {
    return 0;
}

int Assembler::subc(std::istringstream &) {
    return 0;
}

int Assembler::subci(std::istringstream &) {
    return 0;
}

int Assembler::ㅅand(std::istringstream &) {
    return 0;
}

int Assembler::andi(std::istringstream &) {
    return 0;
}

int Assembler::ㅅxor(std::istringstream &) {
    return 0;
}

int Assembler::xori(std::istringstream &) {
    return 0;
}

int Assembler::ㅅcompl(std::istringstream &) {
    return 0;
}

int Assembler::shl(std::istringstream &) {
    return 0;
}

int Assembler::shla(std::istringstream &) {
    return 0;
}

int Assembler::shr(std::istringstream &) {
    return 0;
}

int Assembler::shra(std::istringstream &) {
    return 0;
}

int Assembler::compr(std::istringstream &) {
    return 0;
}

int Assembler::compri(std::istringstream &) {
    return 0;
}

int Assembler::getstat(std::istringstream &) {
    return 0;
}

int Assembler::putstat(std::istringstream &) {
    return 0;
}

int Assembler::jump(std::istringstream &) {
    return 0;
}

int Assembler::jumpl(std::istringstream &) {
    return 0;
}

int Assembler::jumpe(std::istringstream &) {
    return 0;
}

int Assembler::jumpg(std::istringstream &) {
    return 0;
}

int Assembler::call(std::istringstream &) {
    return 0;
}

int Assembler::ㅅreturn(std::istringstream &) {
    return 0;
}

int Assembler::read(std::istringstream &) {
    return 0;
}

int Assembler::write(std::istringstream &) {
    return 0;
}

int Assembler::halt(std::istringstream &) {
    return 0;
}

int Assembler::noop(std::istringstream &) {
    return 0;
}

