#ifndef TANK_H_
#define TANK_H_

#include "../../SDL_Utils/GameObject.h"
#include "../../Managers/App.h"

#include <vector>

class Tank: public GameObject {
public:
    Tank(App* game, int lives, int initialPosHeart);
    virtual ~Tank();

    void handleInput(const SDL_Event &) override;

    void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode shoot);

    inline void setSpeed(float speed){
        speed_ = speed;
    }

    inline void setDeacceletarion(float deacceleration){
        deacceleration_ = deacceleration;
    }   

    void setLife(int life){
        life_ = life;
        std::cout << "Current Life:" << life_ <<  "\n";
    }

    virtual void render();

private:
    App* app_;

    Vector2D vel_;
	float speed_;
    float deacceleration_;
    float life_; 

    std::vector<GameObject*> lives_;
    TankMessageClient::InputType key;
	SDL_Scancode up_, down_, left_, right_, shoot_;
};
#endif