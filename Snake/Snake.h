#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
using namespace std;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 800;
const int NUMB = SCREEN_WIDTH / SCREEN_HEIGHT;

struct Segment
{
    int x;
    int y;
    Segment(int posx, int posy) 
    {
        x = posx;
        y = posy;
    }
};

class Snake 
{

public:
    Snake(int startx, int starty, char dir, SDL_Renderer* ren);
    ~Snake();
    void addSegment(int x, int y);
    void move();
    SDL_Texture* loadTexture(const char* filename);
    void setDirection(char dir);
    void checkCollision();
    void render();
    bool isAlive() { return alive; }
    void checkAndEatFood();

    SDL_Texture* gameOverTexture;

    static const char UP = 0;
    static const char DOWN = 1;
    static const char RIGHT = 2;
    static const char LEFT = 3;

private:
    vector<Segment*> body;
    char direction;
    SDL_Texture* snakeTexture;
    SDL_Renderer* renderer;
    SDL_Texture* foodTexture;
    bool alive;
    Segment* food;
};

