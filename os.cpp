/*
 * This program is a 16 bit CPU virtual machine
 * The virtual machine contains 4 general purpose registers r[0]->r[3]
 * a program counter pc, an instruction counter ir, a stack pointer sp,
 * a clock counter, and an arithmetic logic unit ALU, a 256 word memory mem with
 * base and limit, registers and a disk.
 */

#include "Assembler.h"
#include "VirtualMachine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) { //main program for VM
    Assembler as;
    VirtualMachine vm;

    if (argc == 1) {
        std::cout << "Must supply an input file name.\n";
        exit(1);
    }
    std::string inputFile = argv[1]; //getting the file name
    int pos = inputFile.find("."); //point of the array
    if (pos > inputFile.length() || inputFile[pos+1] != 's') { //checking the array for a .s file
        std::cout << "No .s suffix.\n";
        exit(2);
    }
    std::string name = inputFile.substr(0, pos); //get the name and add .o to the file
    std::string outputFile = name + ".o"; //create file for object code

    std::fstream assembly, objectCode;
    assembly.open(inputFile.c_str(), std::ios::in);
    objectCode.open(outputFile.c_str(), std::ios::out);

    if (as.assemble(assembly, objectCode)) {
        std::cout << "Assembler Error\n";
        assembly.close();
        objectCode.close();
        exit(3);
    }
    assembly.close(); //no errors, close both
    objectCode.close();

    objectCode.open(outputFile.c_str(), std::ios::in);//open input so the VM can read from there
    std::fstream in, out; //put the files in the "ready mode"
    in.open((name + ".in").c_str(), std::ios::in); //opening the input
    out.open((name + ".out").c_str(), std::ios::out); //opening the output

    vm.run(objectCode, in, out); //run the .in and .out files by the use of the VM, it loads the memory then executes
    out << "\nClock = " << vm.get_clock() << std::endl; //print the value of the clock at the end of the program

    objectCode.close();
    in.close();
    out.close();

    return 0;
}