// Registers mapping is as follows:
// SP	-	-	Stack Pointer           - 0 
// PC	-	-	Program Counter/Pointer - 1
// AF	A	-	Accumulator & Flags     - 2
// BC	B	C	BC                      - 3
// DE	D	E	DE                      - 4           
// HL	H	L	HL                      - 5
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class MMU
{

private:
    //RAM
    __uint8_t ram[0xFFFF];
    //Registers
    __uint16_t SP;
    __uint16_t PC;
    __uint8_t A;
    __uint8_t B;
    __uint8_t C;
    __uint8_t D;
    __uint8_t E;
    __uint8_t H;
    __uint8_t L;   
    bool Z;
    bool N;
    bool HC;
    bool Carry; 

public:
    MMU();
    __uint8_t readByte();
    char * readBootRom(char*);
    char * readCartridge(char*);
    void decodeOpcode(__uint8_t);
friend class cpu;  
};