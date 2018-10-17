//
// Created by Matthew Ramirez on 9/25/18.
//
/* Includes for the Assembler.cpp
 *
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include "Assembler.h"

using namespace std;

Assembler::Assembler() // jump table for opcode
{
    //instructions to read and created object oriented numbers from .s file
	jumpTable["load"] = &Assembler::load;
	jumpTable["loadi"] = &Assembler::loadi;
	jumpTable["store"] = &Assembler::store;
	jumpTable["add"] = &Assembler::add;
	jumpTable["addi"] = &Assembler::addi;
	jumpTable["addc"] = &Assembler::addc;
	jumpTable["addci"] = &Assembler::addci;
	jumpTable["sub"] = &Assembler::sub;
	jumpTable["subi"] = &Assembler::subi;
	jumpTable["subci"] = &Assembler::subc;
	jumpTable["subci"] = &Assembler::subci;
	jumpTable["and"] = &Assembler::aand; //changed because of the reserved name
	jumpTable["andi"] = &Assembler::andi;
	jumpTable["xor"] = &Assembler::axor; //changed because of the reserved name
	jumpTable["xori"] = &Assembler::xori;
	jumpTable["compl"] = &Assembler::acompl; //changed because of the reserved name
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
	jumpTable["return"] = &Assembler::areturn; //changed because of the reserved name
	jumpTable["read"] = &Assembler::read;
	jumpTable["write"] = &Assembler::write;
	jumpTable["halt"] = &Assembler::halt;
	jumpTable["noop"] = &Assembler::noop;
} // Assembler

int Assembler::assemble(fstream& in, fstream& out) { //read assembly code from test programs
	string line;
	string opcode;
	const int success = false;
	const int error = true;
	//const int debug = false;
	int instruction;

	getline(in, line);
	while (!in.eof()) {
		istringstream str(line.c_str());
		str >> opcode;			//read first word from assembly code for each line
		if (opcode[0] == '!') {	//set first word as opcode
			getline(in, line);
			continue;
		}
		try {
			if (not jumpTable[opcode]) {
                throw NullPointerException();
            }
			else {
                instruction = (this->*jumpTable[opcode])(str);
            }
		}
		catch (NullPointerException e) {
			cerr << e.what() << endl;
			return error;
		}

		if (instruction == -1) {
            return error;
        }
		out << instruction << endl;
		getline(in, line);
	}
	return success;
}
/*
 * In each of the following operations, the opcodes are checked from the table and jumps from that table to be read
 * and translated into code. There are 2 formats we use to store the instructions givens which tells us where
 * to place the bits.
 * For the following operations each opcode from the jump table will be
 * read and translated to object code for the program
 * two formats are used for storing operation instructions
 * format 1 =  |15:11 opcode|10:9 RD|8 immediate|7:6 RS|5:0 unused|
 * format 2 =  |15:11 opcode|10:9 RD|8 immediate|7:0 ADDR/CONST|
 * for format 1, 5:0 unused are reserved:
 * |5 doncare|4 overflow|3 Less|2 Equal|1 Greater|0 carry|
 */
int Assembler::load(istringstream & str) {
	int rd, addr;	//the instructions for opcode are created
	str >> rd >> addr; //instructions for opcode are stored
	if (rd < 0 || rd > 3) {//check for rd 0 <= x => 3
        return -1;
    }
	if (addr < 0 || addr > 255) {//test for errors if addr 0< x >255
        return -1;
    }
	int inst = 0; //set opcodes value from jump table
	inst = inst << 11 | rd << 9 | addr;//store instructions based on the formats 1 or 2
	return inst;
}

int Assembler::loadi(istringstream & str) {
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) { //testing the constant -128< x >127
        return -1;
    }
	int inst = 0;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant); //i<<8 is immediate bit
	return inst;											
}

int Assembler::store(istringstream & str) {
	int rd, addr;
	str >> rd >> addr;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 1;
	inst = inst << 11 | rd << 9 | 0 << 8 | addr;
	return inst;
}

int Assembler::add(istringstream & str) {
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

int Assembler::addi(istringstream & str) {
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) {
        return -1;
    }
	int inst = 2;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::addc(istringstream & str) {
	int rd, rs, carry;
	str >> rd >> rs >> carry;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (rs < 0 || rs > 3) {
        return -1;
    }
	int inst = 3;
	inst = inst << 11 | rd << 9 | rs << 6 | carry << 0;
	return inst;
}

int Assembler::addci(istringstream & str) {
	int rd, constant, carry;
	str >> rd >> constant >> carry;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) {
        return -1;
    }
	int inst = 3;
	inst = inst << 11 | rd << 9 | 1 << 8 | carry << 0 | (0x000000ff & constant);
	return inst;
}

int Assembler::sub(istringstream & str) {
	int rd, rs;
	str >> rd >> rs;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (rs < 0 || rs > 3) {
        return -1;
    }
	int inst = 4;
	inst = inst << 11 | rd << 9 | rs << 6;
	return inst;
}

int Assembler::subi(istringstream & str) {
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) {
        return -1;
    }
	int inst = 4;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::subc(istringstream & str) {
	int rd, rs, carry;
	str >> rd >> rs >> carry;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (rs < 0 || rs > 3) {
        return -1;
    }
	int inst = 5;
	inst = inst << 11 | rd << 9 | rs << 6 | carry << 0;
	return inst;
}

int Assembler::subci(istringstream & str) {
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

int Assembler:: aand (istringstream & str) {
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

int Assembler::andi(istringstream & str) {
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

int Assembler:: axor (istringstream & str) {
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

int Assembler::xori(istringstream & str) {
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) {
        return -1;
    }
	int inst = 7;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::acompl(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 8;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::shl(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 9;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::shla(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 10;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::shr(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 11;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::shra(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 12;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::compr(istringstream & str) {
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

int Assembler::compri(istringstream & str) {
	int rd, constant;
	str >> rd >> constant;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	if (constant < -128 || constant > 127) {
        return -1;
    }
	int inst = 13;
	inst = inst << 11 | rd << 9 | 1 << 8 | (0x000000ff & constant);
	return inst;
}

int Assembler::getstat(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 14;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::putstat(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 15;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::jump(istringstream & str) {
	int addr;
	str >> addr;
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 16;
	inst = inst << 11 | 1 << 8 | addr;
	return inst;
}

int Assembler::jumpl(istringstream & str) {
	int addr;
	str >> addr;
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 17;
	inst = inst << 11 | 1 << 8 | addr;
	return inst;
}

int Assembler::jumpe(istringstream & str) {
	int addr;
	str >> addr;
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 18;
	inst = inst << 11 | 1 << 8 | addr;
	return inst;
}

int Assembler::jumpg(istringstream & str) {
	int addr;
	str >> addr;
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 19;
	inst = inst << 11 | 1 << 8 | addr;
	return inst;
}

int Assembler::call(istringstream & str) {
	int addr;
	str >> addr;
	if (addr < 0 || addr > 255) {
        return -1;
    }
	int inst = 20;
	inst = inst << 11 | 1 << 8 | addr;
	return inst;
}

int Assembler::areturn(istringstream & str) {
	int inst = 21;
	inst = inst << 11;
	return inst;
}

int Assembler::read(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 22;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::write(istringstream & str) {
	int rd;
	str >> rd;
	if (rd < 0 || rd > 3) {
        return -1;
    }
	int inst = 23;
	inst = inst << 11 | rd << 9;
	return inst;
}

int Assembler::halt(istringstream & str) {
	int inst = 24;
	inst = inst << 11;
	return inst;
}

int Assembler::noop(istringstream & str) {
	int inst = 25;
	inst = inst << 11;
	return inst;
}
