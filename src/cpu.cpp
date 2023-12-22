#include "cpu.h"

using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;
cpu::cpu(MMU mmu, opcode op_instance) {
    step = (double) 1000/60;
    // current_time = ;
    mmu.ram[0x8000] = 0x1;
    this->mmu = mmu;
    this->op_instance = op_instance;
}
__uint16_t cpu::combined_reg(__uint8_t MSB, __uint8_t LSB) {
    return (MSB << 8 | LSB);
}
void cpu::decodeOpcode(__uint8_t opcode) {
    switch(opcode) {
        case 0x00: break; case 0x01: break; 
        case 0x0F: execute_0E();break;
        case 0x20: execute_20(); break;
        case 0x21: execute_21(); break;
        case 0x31: execute_31(); break;
        case 0x32: execute_32(); break;
        case 0xAF: execute_AF(); break;
        case 0xCB: execute_CB(); break;
    }
    return;
}

void cpu::tick() {
    __uint8_t byte =  mmu.readByte();

    decodeOpcode(byte);
    std::this_thread::sleep_for(std::chrono::nanoseconds(240));
}

void cpu::execute_31() {
    mmu.SP = (mmu.ram[mmu.PC++])|(mmu.ram[mmu.PC++]<<8);
}
void cpu::execute_32() {
    __uint16_t HL = combined_reg(mmu.H,mmu.L);
    mmu.ram[HL--] = mmu.A;
    mmu.H = (HL & 0xFF00)>>8;
    mmu.L = HL & 0xFF;
}
void cpu::execute_AF() {
    mmu.A ^= mmu.A;
    if(!mmu.A) mmu.Z = true;
    mmu.N, mmu.HC, mmu.Carry = false, false, false;
}
void cpu::execute_20() {
    __uint8_t temp;
    if(!mmu.Z) {
        temp = mmu.ram[mmu.PC++];
        temp += (mmu.PC++ & 0xFF);
        // Check This Logic
        mmu.PC = temp;
    }
    else mmu.PC++;
    return;
}
void cpu::execute_21() {
    mmu.L = mmu.ram[mmu.PC++];
    mmu.H = mmu.ram[mmu.PC++];
}
void cpu::execute_0E() {
    return;
}
void cpu::execute_CB() {
    __uint8_t ext_opcode = mmu.ram[mmu.PC++];
    switch(ext_opcode) {
        case 0x7C: 
            mmu.Z = execute_CB_bit(7,mmu.H);
            mmu.N, mmu.HC = false, true;
            break;
    }
}
bool cpu::execute_CB_bit(int pos, __uint8_t reg) {
    return !(reg>>pos);
}
