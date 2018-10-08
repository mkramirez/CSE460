#include "VirtualMachine.h"

//fetch the pc out of the memory
//opcode is sitting in the bits 11-15 the opcode is ir&0xf800 and you are "shitfing it" 11 times 0->10
//RD is sitting 9-10 opcode is (ir&0x600) 9 times

/*
    instr[0] = &VirtualMachine::load;
    instr[1] = &VirtualMachine::store;
    instr[2] = &VirtualMachine::add;
    instr[3] = &VirtualMachine::addc;
    instr[4] = &VirtualMachine::addci;
    instr[5] = &VirtualMachine::sub;
    instr[6] = &VirtualMachine::subc;
    instr[7] = &VirtualMachine::ㅅand;
    instr[8] = &VirtualMachine::ㅅxor;
    instr[9] = &VirtualMachine::ㅅcompl;
    instr[10] = &VirtualMachine::shl;
    instr[11] = &VirtualMachine::shla;
    instr[12] = &VirtualMachine::shr;
    instr[13] = &VirtualMachine::shra;
    instr[14] = &VirtualMachine::compr;
    instr[15] = &VirtualMachine::getstat;
    instr[16] = &VirtualMachine::putstat;
    instr[17] = &VirtualMachine::jump;
    instr[18] = &VirtualMachine::jumpl;
    instr[19] = &VirtualMachine::jumpe;
    instr[20] = &VirtualMachine::jumpg;
    instr[21] = &VirtualMachine::call;
    instr[22] = &VirtualMachine::ㅅreturn;
    instr[23] = &VirtualMachine::read;
    instr[24] = &VirtualMachine::write;
    instr[25] = &VirtualMachine::halt;
    instr[26] = &VirtualMachine::noop;
*/

void VirtualMachine::run(std::fstream& objectCode, std::fstream& in, std::fstream& out) {
    const int debug = false;
    int opcode, rd, i, rs, constant, addr, j;

    base = 0;
    for (limit = 0; objectCode >> mem[limit]; limit++);
    sr = 2;
    sp = msize;
    pc = 0;
    while (pc < limit) {
        ir = mem[pc];
        pc++;
        opcode = (ir & 0xf800) >> 11;
        rd = (ir & 0x600) >> 9;
        i = (ir & 0x100) >> 8;
        rs = (ir & 0xc0) >> 6;
        addr = ir & 0xff;
        constant = addr;
        if (ir & 0x80) constant |= 0xffffff00; // if neg sign extend

        clock++;

        if (opcode == 0) { /* load and loadi */
            if (i) {
                r[rd] = constant;
            }
            else {
                r[rd] = mem[addr];
                clock += 3;
            }
        }
        else if (opcode == 1) { /* store */
            mem[addr] = r[rd];
            clock += 3;
        }
        else if (opcode == 2) { /* add and addi */
            if (i) {
                r[rd] = r[rd] + constant;
            }
            else {
                r[rd] = r[rd] + r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            }
            else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            }
            else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 3) { //addc and addci
            if (i) {
                r[rd] = r[rd] + constant;
            }
            else {
                r[rd] = r[rd] + r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            }
            else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            }
            else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 4) { //sub and subi
            if (i) {
                r[rd] = r[rd] - constant;
            }
            else {
                r[rd] = r[rd] - r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            }
            else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            }
            else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 5) { //subc and subci
            if (i) {
                r[rd] = r[rd] - constant;
            }
            else {
                r[rd] = r[rd] - r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            }
            else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            }
            else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 6) { //and and andi
            if (i) {
                r[rd] = r[rd] - constant;
            }
            else {
                r[rd] = r[rd] - r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            }
            else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            }
            else {
                r[rd] &= 0xffff;
            }
        }
        else {
            std::cout << "Bad opcode = " << opcode << std::endl;
            exit(3);
        }
        if (debug) {
            for (j = 0; j < limit; j++) {
                printf("%8d", mem[j]);
                if ((j % 8) == 7) printf("\n");
            }
            cout << endl;
        }
    }
}

int VirtualMachine::get_clock() {
    return clock;
}

void VirtualMachine::load() {
    clock += 4;

}

void VirtualMachine::loadi() {
    clock += 1;

}

void VirtualMachine::store() {
    clock += 4;
}

void VirtualMachine::add() {
    clock += 1;
}

void VirtualMachine::addi() {
    clock += 1;
}

void VirtualMachine::addc() {
    clock += 1;
}

void VirtualMachine::addci() {
    clock += 1;
}

void VirtualMachine::sub() {
    clock += 1;
}

void VirtualMachine::subi() {
    clock += 1;
}

void VirtualMachine::subc() {
    clock += 1;
}

void VirtualMachine::subci() {
    clock += 1;
}

void VirtualMachine::ㅅand() {
    clock += 1;
}

void VirtualMachine::andi() {
    clock += 1;
}

void VirtualMachine::ㅅxor() {
    clock += 1;
}

void VirtualMachine::xori() {
    clock += 1;
}

void VirtualMachine::ㅅcompl() {
    clock += 1;
}

void VirtualMachine::shl() {
    clock += 1;
}

void VirtualMachine::shla() {
    clock += 1;
}

void VirtualMachine::shr() {
    clock += 1;
}

void VirtualMachine::shra() {
    clock += 1;
}

void VirtualMachine::compr() {
    clock += 1;
}

void VirtualMachine::compri() {
    clock += 1;
}

void VirtualMachine::getstat() {
    clock += 1;
}

void VirtualMachine::putstat() {
    clock += 1;
}

void VirtualMachine::jump() {
    clock += 1;
}

void VirtualMachine::jumpl() {
    clock += 1;
}

void VirtualMachine::jumpe() {
    clock += 1;
}

void VirtualMachine::jumpg() {
    clock += 1;
}

void VirtualMachine::call() {
    clock += 4;
}

void VirtualMachine::ㅅreturn() {
    clock += 4;
}

void VirtualMachine::read() {
    clock += 28;
}

void VirtualMachine::write() {
    clock += 28;
}

void VirtualMachine::halt() {
    clock += 1;
}

void VirtualMachine::noop() {
    clock += 1;
}

