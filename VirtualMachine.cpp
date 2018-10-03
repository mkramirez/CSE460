#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
    r = std::vector <int> (REG_FILE_SIZE);
    mem = std::vector <int> (MEM_SIZE);
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
