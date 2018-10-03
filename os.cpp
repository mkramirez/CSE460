#include "Assembler.h"
#include "VirtualMachine.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Assembler as;
    VirtualMachine vm;

    if (argc == 1) {
        std::cout << "Must supply an input file name.\n";
        exit(1);
    }
    std::string inputFile = argv[1];
    int pos = inputFile.find(".");
    if (pos > inputFile.length() || inputFile[pos+1] != 's') {
        std::cout << "No .s suffix.\n";
        exit(2);
    }
    std::string name = inputFile.substr(0, pos);
    std::string outputFile = name + ".o";

    std::fstream assembly, objectCode;
    assembly.open(inputFile.c_str(), std::ios::in);
    objectCode.open(outputFile.c_str(), std::ios::out);

    if (as.assemble(assembly, objectCode)) {
        std::cout << "Assembler Error\n";
        assembly.close();
        objectCode.close();
        exit(3);
    }
    assembly.close();
    objectCode.close();

    objectCode.open(outputFile.c_str(), std::ios::in);
    std::fstream in, out;
    in.open((name + ".in").c_str(), std::ios::in);
    out.open((name + ".out").c_str(), std::ios::out);

    vm.run(objectCode, in, out);
    out << "\nClock = " << vm.get_clock() << std::endl;

    objectCode.close();
    in.close();
    out.close();

    return 0;
}