#include <iostream>
#include <fstream>
#include "cpu.h"
#include "ppu.h"
#include <SDL2/SDL.h>
using namespace std;

int main(int argc, char *argv[]) {
    // Class Declaration

    ppu ppu_instance = ppu();
    MMU mmu = MMU();
    mmu.readCartridge((char *)"/home/avinash/GameBoy/Extra/Tetris.gb");
    mmu.readBootRom((char *)"../Extra/DMG_ROM.bin");
    opcode op_instance = opcode();
    cpu cpu_instance = cpu(mmu, op_instance);

    // Game Loop
    while (!cpu_instance.quit) {
        if (SDL_PollEvent(&cpu_instance.e) && cpu_instance.e.type == SDL_QUIT) {
            cpu_instance.quit = true;
            break;
        }
        cpu_instance.tick();
    }   

}
