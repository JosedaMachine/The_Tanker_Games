#include <vector>
#include <SDL2/SDL.h>

class GameObject;
class SDL_Renderer;

class Game{
public:
     Game();
     virtual ~Game();
     void init(int w, int h);
     void start();
private:
    std::vector<GameObject*> objs_;
    SDL_Renderer* rend;
    SDL_Window* win;
    SDL_Texture* tex;
    int speed, close;
    int width_, height_;
    SDL_Rect dest;
};