#include <iostream>
#include <time.h>
#include <chrono>
#include "cpu.h"
#include <SDL2/SDL.h>
using namespace std;

// window size declaration
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;


// Change the cycle
int main() {
    cpu cpu_instance = cpu();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    SDL_CreateWindowAndRenderer( SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    //Fill the surface white
    // SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x0, 0x0, 0x0 ) );
            
    //Update the surface
    SDL_UpdateWindowSurface( window );

    int i = 0;
    SDL_Event e;
    // bool quit = false; 
    cpu_instance.startFrame = chrono::steady_clock::now();
    while (1) {
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT)
            break;
        // cout << finish << endl;
        SDL_RenderDrawPoint(renderer, 0, 0);
        cpu_instance.finishFrame = std::chrono::steady_clock::now();
        auto timeTook = std::chrono::duration_cast<std::chrono::milliseconds>(cpu_instance.finishFrame - cpu_instance.startFrame).count();

        if(timeTook > cpu_instance.step) {
            cpu_instance.startFrame = std::chrono::steady_clock::now();
            cout << i << endl;
            // SDL_RenderDrawPoint(renderer, i, i);
            i++;
        }
    }   


}
