#include <SDL2/SDL.h>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;
class ppu
{
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;
public:
    ppu();
};

