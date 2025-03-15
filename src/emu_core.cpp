#include <iostream>
#include <fstream>
#include "cpu.h"
#include "ppu.h"
#include <SDL2/SDL.h>
using namespace std;
int main(int argc, char *argv[]) {
    // Object Declaration
    ppu ppu_instance = ppu();
    MMU mmu = MMU();
    opcode op_instance = opcode();
    // Catrdige path and the boot rom path
    // Need to make this dynamic
    mmu.readCartridge((char *)"/home/avinash/GameBoy/Extra/Tetris.gb");
    mmu.readBootRom((char *)"../Extra/DMG_ROM.bin");
    cpu cpu_instance = cpu(mmu, op_instance);

    // Game Loop
    while (!cpu_instance.quit) {
        // If the close button is clicked on the UI, the loop breaks closing the game
        if (SDL_PollEvent(&cpu_instance.e) && cpu_instance.e.type == SDL_QUIT) {
            cpu_instance.quit = true;
            break;
        }
        cpu_instance.tick();
    }   

}
