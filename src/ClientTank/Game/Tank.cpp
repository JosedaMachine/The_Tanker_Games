#include "Tank.h"

#include "../SDL_Utils/Environment.h"
#include "../Managers/GameManager.h"

#include "Heart.h"

Tank::Tank(TankClient* game, int lives, int initialPosHeart) : GameObject(), vel_(), speed_(0) , deacceleration_(0.5), life_(lives) {
	app_ = game;
	const int SIZE_HEART = 50;
	for(int i = 0; i < life_ ; i++){
		Heart* h = new Heart();
		h->setTransform(initialPosHeart + i*SIZE_HEART, 10);
		h->setDimensions(SIZE_HEART, SIZE_HEART);
		h->setTexture("./resources/images/heart.png");
		lives_.push_back(h);
	}
}

Tank::~Tank() {}

void Tank::handleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN){
		key = TankMessageClient::InputType::NONE; 
		if (e.key.keysym.scancode == up_){
			key = TankMessageClient::InputType::FRONT; 
			// vel_ = vel_ + Vector2D(0, -1).rotate(rotation) * speed_;
		}
		else if (e.key.keysym.scancode == down_){
			key = TankMessageClient::InputType::BACK;
			// vel_ = vel_ + Vector2D(0, 1).rotate(rotation) * 0.7f *speed_;
		}
		
		if (e.key.keysym.scancode == left_){
			key = TankMessageClient::InputType::LEFT;
			// rotation = (rotation - 5.0f);
		}
		else if (e.key.keysym.scancode == right_){
			key = TankMessageClient::InputType::RIGHT;
			// rotation = (rotation + 5.0f);
		}

		if(e.key.keysym.scancode == shoot_){
			key = TankMessageClient::InputType::SHOOT;
			// shoot();
		}
		app_->sendGameMessage(key);
	}
}

void Tank::render(){
	GameObject::render();

	for (size_t i = 0; i < life_; i++){
		lives_[i]->render();
	}
}

void Tank::setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode shoot)
{
	up_ = up;
	down_ = down;
	left_ = left;
	right_ = right;
	shoot_ = shoot;
}