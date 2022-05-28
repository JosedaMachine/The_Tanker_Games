#ifndef TANK_H_
#define TANK_H_

#include "GameObject.h"

class Tank: public GameObject {
public:
    Tank();
    virtual ~Tank();

    void handleInput(const SDL_Event &) override;
    void update() override;

    void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right);

    inline void setSpeed(float speed){
        speed_ = speed;
    }

private:
    Vector2D vel_;
	float speed_;

	SDL_Scancode up_, down_, left_, right_;
};
#endif