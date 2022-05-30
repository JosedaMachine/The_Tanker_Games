#ifndef TANK_H_
#define TANK_H_

#include "GameObject.h"
#include <vector>

class Tank: public GameObject {
public:
    Tank(std::vector<GameObject *>* objs_);
    virtual ~Tank();

    void handleInput(const SDL_Event &) override;
    void update() override;

    void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode shoot);

    inline void setSpeed(float speed){
        speed_ = speed;
    }

    inline void setDeacceletarion(float deacceleration){
        deacceleration_ = deacceleration;
    }
    
private:

    void shoot();

    Vector2D vel_;
	float speed_;
    float deacceleration_; 

    std::vector<GameObject *>* gameObjs_;

	SDL_Scancode up_, down_, left_, right_, shoot_;
};
#endif