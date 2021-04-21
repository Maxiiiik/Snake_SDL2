#include "Snake.h"
using namespace std;
Snake::Snake(int startx, int starty, char dir, SDL_Renderer* ren)
{
    direction = dir;
    renderer = ren;
    alive = true;
    snakeTexture = loadTexture("person.png");
    gameOverTexture = loadTexture("GameOver.png");
    foodTexture = loadTexture("point.png");
    food = new Segment(0, 0);
    do
    {
        food->x = rand() % NUMB;
        food->y = rand() % NUMB;
    }   
    while (food->x != startx && food->y != starty);
    addSegment(startx, starty);
}

Snake::~Snake() 
{
    for (int i = 0; i < body.size(); i++)
        delete body[i];
}

void Snake::addSegment(int x, int y) 
{
    Segment* seg = new Segment(x, y);
    body.push_back(seg);
}

void Snake::move()
{
    if (!alive) return;
    int dx, dy;
    switch (direction)
    {
    case Snake::UP:
        dx = 0;
        dy = -1;
        break;
    case Snake::DOWN:
        dx = 0;
        dy = 1;
        break;
    case Snake::RIGHT:
        dx = 1;
        dy = 0;
        break;
    case Snake::LEFT:
        dx = -1;
        dy = 0;
        break;
    default:
        break;
    }
    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
    }
    Segment* snakeHead = *(body.begin());
    snakeHead->x += dx;
    snakeHead->y += dy;
}

SDL_Texture* Snake::loadTexture(const char* filename) 
{
    SDL_Surface* tSurface = IMG_Load(filename);
    if (!tSurface)
        cout << "ERROR!!!!!  load image " << filename << " : " << IMG_GetError() << endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tSurface);
    SDL_FreeSurface(tSurface);
    return texture;
}

void Snake::setDirection(char dir)
{
    switch (direction)
    {
    case Snake::UP:
        if (dir == Snake::UP) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case Snake::DOWN:
        if (dir == Snake::DOWN) return;
        if (body.size() > 1 && body[0]->y == body[1]->y) return;
        break;
    case Snake::RIGHT:
        if (dir == Snake::RIGHT) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
        break;
    case Snake::LEFT:
        if (dir == Snake::LEFT) return;
        if (body.size() > 1 && body[0]->x == body[1]->x) return;
        break;
    }
    direction = dir;
}

void Snake::checkCollision()
{
    Segment* head = body[0];
    if (head->x < 0 || head->x > NUMB - 1 || head->y < 0 || head->y > NUMB - 1) 
    {
        alive = false;
        return;
    }
    for (int i = 1; i < body.size(); i++) 
    {
        if (head->x == body[i]->x && head->y == body[i]->y)
        {
            alive = false;
            break;
        }
    }
}