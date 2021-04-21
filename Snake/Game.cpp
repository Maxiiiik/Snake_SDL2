#include "Game.h"
using namespace std;
Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    running = false;
    snake = nullptr;
}

Game::~Game() 
{
    delete snake;
}

void Game::init(const char* title, int posx, int posy, int width, int height, bool maximised)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "ERROR!!!!!! SDL " << SDL_GetError() <<endl;
        return;
    }
    window = SDL_CreateWindow(title, posx, posy, width, height, maximised == true ? SDL_WINDOW_MAXIMIZED : NULL);
    if (window == NULL) 
    {
        cout << "ERROR!!!!!!! window " << SDL_GetError() << endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, NULL);
    if (renderer == NULL) 
    {
        cout << "ERROR!!!!!!!! render " << SDL_GetError() << endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
    running = true;
    snake = new Snake(NUMB / 2, NUMB / 2, rand() % 4, renderer);
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_KEYDOWN) 
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                snake->setDirection(Snake::UP);
                break;
            case SDLK_DOWN:
                snake->setDirection(Snake::DOWN);
                break;
            case SDLK_LEFT:
                snake->setDirection(Snake::RIGHT);
                break;
            case SDLK_RIGHT:
                snake->setDirection(Snake::LEFT);
                break;
            case SDLK_RETURN:
                if (!snake->isAlive()) running = false;
                break;
            default:
                break;
            }
        }
        else if (event.type == SDL_QUIT) running = false;
    }
}

void Game::check() 
{
    if (snake->isAlive())
    {
        snake->checkCollision();
        snake->checkAndEatFood();
        snake->move();
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    snake->render();
    if (!snake->isAlive()) 
    {
        SDL_Rect r;
        r.w = 120;
        r.h = 80;
        r.x = (SCREEN_WIDTH - r.w) / 2;
        r.y = (SCREEN_HEIGHT - r.h) / 2;
        SDL_RenderCopy(renderer, snake->gameOverTexture, NULL, &r);
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}