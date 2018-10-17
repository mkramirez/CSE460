//
// Created by Matthew Ramirez on 9/25/18.
//
//Header for the Assembler.cpp
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>

class NullPointerException : public std::runtime_error {
public:
	NullPointerException() : runtime_error("Null Function Pointer!") { }
};

class Assembler 
{
	typedef int (Assembler::*FP)(std::istringstream &);
	std::map<std::string, FP> jumpTable;	//set up jump table
public:
	Assembler();
	int assemble(std::fstream&, std::fstream&);	//functions for every opcode
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
	int aand(std::istringstream &);
	int andi(std::istringstream &);
	int axor(std::istringstream &);
	int xori(std::istringstream &);
	int acompl(std::istringstream &);
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
	int areturn(std::istringstream &);
	int read(std::istringstream &);
	int write(std::istringstream &);
	int halt(std::istringstream &);
	int noop(std::istringstream &);
}; // Assembler

#endif


