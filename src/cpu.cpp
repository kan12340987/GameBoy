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
    __uint16_t temp = (MSB << 8 | LSB);
    return temp;
}
void cpu::decodeOpcode(__uint8_t opcode) {
    switch(opcode) {
        // Instruction for NOP
        case 0x00: break; 
        case 0x01: load_rr_nn(opcode, mmu.B, mmu.C); break;
        case 0x11: load_rr_nn(opcode, mmu.D, mmu.E); break;
        case 0x21: load_rr_nn(opcode, mmu.H, mmu.L); break;
        case 0x31: load_rr_nn(opcode, mmu.B, mmu.C); break;
        case 0x0E: execute_ld_r_n(mmu.C);break;
        case 0x1E: execute_ld_r_n(mmu.E);break;
        case 0x2E: execute_ld_r_n(mmu.L);break;
        case 0x3E: execute_ld_r_n(mmu.A);break;
        case 0x20: execute_jr_cc_e(!mmu.Z); break;
        case 0x30: execute_jr_cc_e(!mmu.Carry); break;
        case 0x28: execute_jr_cc_e(mmu.Z == 0); break;
        case 0x38: execute_jr_cc_e(mmu.Carry == 0); break;

        case 0x32: indirect_hl_decrement(); break;
        case 0xA8: xor_r(mmu.B); break;
        case 0xA9: xor_r(mmu.C); break;
        case 0xAA: xor_r(mmu.D); break;
        case 0xAB: xor_r(mmu.E); break;
        case 0xAC: xor_r(mmu.H); break;
        case 0xAD: xor_r(mmu.L); break;
        case 0xAF: xor_r(mmu.A); break;
        case 0xCB: execute_CB(); break;
    }
    return;
}
// A dynamic wait function for M-Cycle
void cpu::waitcycle(int m_cycle) {
    for(int i = 0; i < m_cycle; i++)
        std::this_thread::sleep_for(std::chrono::microseconds(1));

}
// One cycle of the Emulator
void cpu::tick() {
    // Read the byte in the RAM
    __uint8_t byte =  mmu.readByte();
    // Sleep set to sync the modern PC with the slower GB clock
    waitcycle(1);
    decodeOpcode(byte);
}
// LD rr, nn
void cpu::load_rr_nn(int opcode,__uint8_t &msb, __uint8_t &lsb) {
    if(opcode == 0x31) {
        mmu.SP = (mmu.ram[mmu.PC++])|(mmu.ram[mmu.PC++]<<8);
    } else {
        lsb = (mmu.ram[mmu.PC++]);
        msb = (mmu.ram[mmu.PC++]);
    }
    waitcycle(2);
}
// XOR r
void cpu::xor_r(__uint8_t &reg) {
    mmu.A ^= reg;
    if(!mmu.A) mmu.Z = true;
    mmu.N, mmu.HC, mmu.Carry = false, false, false;
    //No waiting needed
}
// LD (HL-), A
void cpu::indirect_hl_decrement() {
    __uint16_t HL = combined_reg(mmu.H,mmu.L);
    mmu.ram[HL--] = mmu.A;
    mmu.H = (HL & 0xFF00)>>8;
    mmu.L = HL & 0xFF;
}

void cpu::execute_jr_cc_e(bool condition) {
    __uint8_t temp;
    if(condition) {
        temp = mmu.ram[mmu.PC++];
        temp += (mmu.PC++ & 0xFF);
        // Check This Logic
        mmu.PC = temp;
        waitcycle(1);
    }
    else {
        mmu.PC++;
        waitcycle(2);
    }
    return;
}

// LD r, n
void cpu::execute_ld_r_n(__uint8_t &reg) {
    reg = mmu.ram[mmu.PC++];
    waitcycle(1);
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
    waitcycle(2);
}
bool cpu::execute_CB_bit(int pos, __uint8_t reg) {
    return !(reg>>pos);
}
