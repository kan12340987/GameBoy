#include <iostream>
using namespace std;
//Using SDL and standard IO
 #include <SDL2/SDL.h>
 const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main() {
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
    //Update the surface
    SDL_UpdateWindowSurface( window );

    //Hack to get window to stay up
    SDL_Event e;
     bool quit = false; 
     while( quit == false ){
         while( SDL_PollEvent( &e ) )
         { 
            if( e.type == SDL_QUIT ) 
            quit = true; 
        } 
    }
}
