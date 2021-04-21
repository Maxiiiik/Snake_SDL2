#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <cstdlib>
#include "Snake.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 800;
const int NUMB = SCREEN_WIDTH / SCREEN_HEIGHT;
class Game 
{

public:
    Game();
    ~Game();
    void init(const char* title, int posx, int posy, int width, int height, bool maximised);
    void handleEvents();
    void check();
    void render();
    void clean();
    bool isRunning() { return running; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Snake* snake;
};