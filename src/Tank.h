#include "GameObject.h"

class Tank: public GameObject{
public:
    Tank(int w, int h, SDL_Renderer* rend);
    virtual ~Tank();

    void handleInput(const SDL_Event &) override;
    void update() override;
    void render() override;

    inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop){
        up_ = up;
        down_ = up;
        stop_ = up;
    }

    inline void setSpeed(float speed){
        speed_ = speed;
    }

private:
    SDL_Color color_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
    SDL_Renderer* renderer_;
    int heightApp_, widthApp_;
};