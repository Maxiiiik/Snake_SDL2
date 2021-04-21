#include "Game.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 800;

Game* game = nullptr;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    const int frameRate = 30;
    const int frameDelay = 1000 / frameRate;

    Uint32 frameTime;
    int frameElapsedTime;

    game = new Game();
    game->init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    while (game->isRunning()) {
        frameTime = SDL_GetTicks();

        game->handleEvents();
        game->check();
        game->render();

        frameElapsedTime = SDL_GetTicks() - frameTime;
        if (frameDelay > frameElapsedTime)
            SDL_Delay(frameDelay - frameElapsedTime);
    }
    game->clean();
    return 0;
}