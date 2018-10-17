/*fetch the pc out of the memory
 * Format #1
 * opcode is sitting in the bits 11-15 the opcode is ir&0xf800 and you are "shitfing it" 11 times 0->10
 * RD is sitting 9-10 opcode is (ir&0x600) 9 times
 * i is sitting at 8
 * rs is sitting at 7-6
 * 0-5 is unused
 *
 * Format #2
 * opcode is sitting in 11-15
 * RD 9-10
 * i is at 8
 * Addr/Const 7-0
 *
 * the class virtual machine is the logic for every instruction
 * this class will build and execute every instruction
 * below the opcode is evaluated and the following instructions are performed for each opcode
*/
#include <sstream>
#include "VirtualMachine.h"

void VirtualMachine::run(std::fstream& objectCode, std::fstream& in, std::fstream& out) {
    const int debug = false;
    int opcode, rd, i, rs, constant, addr, j;

    base = 0;
    for (limit = 0; objectCode >> mem[limit]; limit++); //evaluates how many lines of code set limit to this amount
    sr = 2;
    sp = msize;
    pc = 0;
    while (pc < limit) {   //while pc is less than limit set constructors
        ir = mem[pc];
        pc++;
        opcode = (ir & 0xf800) >> 11;
        rd = (ir & 0x600) >> 9;
        i = (ir & 0x100) >> 8;
        rs = (ir & 0xc0) >> 6;
        addr = ir & 0xff;
        constant = addr;
        if (ir & 0x80) constant |= 0xffffff00; // if neg sign extend

        clock++; //implement the clock and +1 for every iteration
        //for the following code instructions are executed

        if (opcode == 0) { /* load and loadi */
            if (i) {
                r[rd] = constant;
            } else {
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
            } else {
                r[rd] = r[rd] + r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 3) { //addc and addci
            if (i) {
                r[rd] = r[rd] + constant + (sr & 1); //sr & 1 is the left most bit or the carry bit
            } else {
                r[rd] = r[rd] + r[rs] + (sr & 1);
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 4) { //sub and subi
            if (i) {
                r[rd] = r[rd] - constant;
            } else {
                r[rd] = r[rd] - r[rs];
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 5) { //subc and subci
            if (i) {
                r[rd] = r[rd] - constant - (sr & 1);
            } else {
                r[rd] = r[rd] - r[rs] - (sr & 1);
            }
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 6) { //and and andi
            if (i) {
                r[rd] = r[rd] & constant;
            } else {
                r[rd] = r[rd] & r[rs];
            }
        }
        else if (opcode == 8) { //compl
            r[rd] = ~r[rd];
        }
        else if (opcode == 9) { //shl
            r[rd] = r[rd] << 1;
            r[0] = 0;
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
        }
        else if (opcode == 10) { //shla
            //shl arithmetic
            r[rd] = r[rd] << 1;
            r[0] = 0;
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 11) { //shr
            //	r[RD] = r[RD] >> 1, shift-in-bit = 0
            r[rd] = r[rd] >> 1;
            r[15] = 0;
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
        }
        else if (opcode == 12) { //shra
            //shr arithmetic
            r[rd] = r[rd] >> 1;
            r[15] = 0;
            // set CARRY
            if (r[rd] & 0x10000) {
                sr |= 01;
            } else {
                sr &= 0xe;
            }
            // sign extend
            if (r[rd] & 0x8000) {
                r[rd] |= 0xffff0000;
            } else {
                r[rd] &= 0xffff;
            }
        }
        else if (opcode == 13) { //compr , compri
            if (i) {
                if (r[rd] < constant) { //if r[RD] < r[RS] set LESS reset EQUAL and GREATER;
                    r[3] = 1;
                    r[2] = 0;
                    r[1] = 0;
                }
                else if (r[rd] == constant) { //if r[RD] == r[RS] set EQUAL reset LESS and GREATER;
                    r[3] = 0;
                    r[2] = 1;
                    r[1] = 0;
                }
                else if (r[rd] > constant) { //if r[RD] > r[RS] set GREATER reset EQUAL and LESS
                    r[3] = 0;
                    r[2] = 0;
                    r[1] = 1;
                }
            }
            else {
                if (r[rd] < r[rs]) { //if r[RD] < CONST set LESS reset EQUAL and GREATER
                    r[3] = 1;
                    r[2] = 0;
                    r[1] = 0;
                }
                else if (r[rd] == r[rs]) { //if r[RD] == CONST set EQUAL reset LESS and GREATER;
                    r[3] = 0;
                    r[2] = 1;
                    r[1] = 0;
                }
                else if (r[rd] > r[rs]) { //if r[RD] > CONST set GREATER reset EQUAL and LESS
                    r[3] = 0;
                    r[2] = 0;
                    r[1] = 1;
                }
            }
        }
        else if (opcode == 14) { //getstat
            //	r[RD] = SR
            r[rd] = sr;
        }
        else if (opcode == 15) { //putstat
            //SR = r[RD]
            sr = r[rd];
        }
        else if (opcode == 16) { //jump
            //pc = ADDR
            pc = addr;
        }
        else if (opcode == 17) { //jumpl
            //if LESS == 1, pc = ADDR, else do nothing
            if (r[3] == 1) {
                pc = addr;
            }
            else {}
        }
        else if (opcode == 18) { //jumpe
            //if EQUAL == 1, pc = ADDR, else do nothing
            if (r[2] == 1) {
                pc = addr;
            }
            else {}
        }
        else if (opcode == 19) { //jumpg
            //if GREATER == 1, pc = ADDR, else do nothing
            if (r[1] == 1) {
                pc = addr;
            } else {}
        }
        else if (opcode == 20) { //call
            //push VM status; pc = ADDR
            if (sp < limit + 6) {
                std::cout << "ERROR STACK FULL!";
                std::cout << std::endl << "Cannot perform CALL operation";
                std::cin.get();
            }
            else { //push VM status onto stack
                mem[sp - 1] = pc;
                mem[sp - 2] = sr;
                mem[sp - 3] = r[0];
                mem[sp - 4] = r[1];
                mem[sp - 5] = r[2];
                mem[sp - 6] = r[3];
                this->sp = sp - 6; //set new stack pointer
                clock += 3;
                pc = addr;
            }
        }
        else if (opcode == 21) { //return
            //pop and restore VM status
            if (sp >= msize) {
                //stack is empty
            }
            else {
                // load values stored in memory to pc, sr, r0, r1, r2, r3
                pc = mem[sp + 5];
                std::cout << pc << std::endl;
                sr = mem[sp + 4];
                r[0] = mem[sp + 3];
                r[1] = mem[sp + 2];
                r[2] = mem[sp + 1];
                r[3] = mem[sp];
                //pop used values off the stack
                mem[sp + 5] = 0;
                mem[sp + 4] = 0;
                mem[sp + 3] = 0;
                mem[sp + 2] = 0;
                mem[sp + 1] = 0;
                mem[sp] = 0;
                if (sp < msize - 6) {
                    sp = sp + 6; // set new stack pointer
                } else {
                    sp = msize;
                }
            }
            clock += 3;
        }
        else if (opcode == 22) { //read
            //read new content of r[RD] from .in file
            std::string line;
            getline(in, line);
            std::istringstream str(line.c_str());
            str >> r[rd];
            clock += 27;
        }
        else if (opcode == 23) { //write
            //write r[RD] into .out file
            out << r[rd] << std::endl;
            clock += 27;
        }
        else if (opcode == 24) { //halt
            //halt execution
            break;
        }
        else if (opcode == 25) { //noop
            //no operation
        }
        else {
            std::cout << "Bad opcode = " << opcode << std::endl;
            exit(3);
        }
        if (debug) //for debugging add ! infront of debug
        {
            printf("ir=%d op=%d rd=%d i=%d rs=%d const=%d addr=%d\n", ir, opcode, rd, i, rs, constant, addr);
            printf("r[0]=%d r[1]=%d r[2]=%d r[3]=%d pc=%d sr=%d sp=%d clock=%d\n\n", r[0], r[1], r[2], r[3], pc, sr, sp,
                   clock);
            //char c;
            //cin>>c;
        }
        if (debug) { //for debugging add ! infront of debug
            for (j = 0; j < limit; j++) {
                printf("%8d", mem[j]);
                if ((j % 8) == 7) printf("\n");
            }
            std::cout << std::endl;
        }
    }
}

int VirtualMachine::get_clock() {
    return clock;
}
