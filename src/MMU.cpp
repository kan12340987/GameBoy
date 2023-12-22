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
    ifstream file(filePath,ios::binary);
    file.read((char *)ram, 0x100);
    return NULL;
}
char * MMU::readCartridge(char * filePath) {
    ifstream file(filePath,ios::binary);
    file.read((char *)ram, 0x7FFF);
    return NULL;
}
void MMU::decodeOpcode(__uint8_t opcode) {

}