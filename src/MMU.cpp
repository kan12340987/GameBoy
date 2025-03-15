#include "MMU.h"
using namespace std;

MMU::MMU() {
    PC = 0x0;
    // inst = instructions(this);
}
__uint8_t MMU::readByte() {
    return ram[PC++];
}
char * MMU::readBootRom(char * filePath) {
    ifstream DMG_ROM(filePath,ios::binary);
    DMG_ROM.seekg(0, std::ios::end);
    long size = DMG_ROM.tellg();
    DMG_ROM.seekg(0, std::ios::beg);
    DMG_ROM.read((char *)ram, 0x100);
    return NULL;
}
char * MMU::readCartridge(char * filePath) {
    ifstream file(filePath,ios::binary);
    file.read((char *)ram, 0x7FFF);
    return NULL;
}
void MMU::decodeOpcode(__uint8_t opcode) {

}