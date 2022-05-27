// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "GameObject.h"

class Paddle: public GameObject {
public:
	Paddle();
	Paddle(SDL_Color color);
	virtual ~Paddle();

	void handleInput(const SDL_Event&) override;
	void update() override;
	void render() override;

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

private:
	SDL_Color color_;
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
};

