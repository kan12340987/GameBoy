#include <iostream>
#include "cpu.h"
#include "ppu.h"
#include <SDL2/SDL.h>
using namespace std;

int main() {
    cpu cpu_instance = cpu();
    ppu ppu_instance = ppu();
    SDL_Event e;
    bool quit = false; 


    while (!quit) {
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT) {
            quit = true;
            break;
        }
        cpu_instance.tick();
    }   

}
