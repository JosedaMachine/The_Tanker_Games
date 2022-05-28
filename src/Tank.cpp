#include "Tank.h"

#include "Environment.h"

Tank::Tank() : GameObject(), vel_(), speed_(0) {}

Tank::~Tank() {}

void Tank::handleInput(const SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.scancode == up_)
			vel_.setY(-speed_);
		else if (e.key.keysym.scancode == down_)
			vel_.setY(speed_);
		else if (e.key.keysym.scancode == left_)
			vel_.setX(-speed_);
		else if (e.key.keysym.scancode == right_)
			vel_.setX(speed_);
	}
}

void Tank::update()
{
	tr_ = tr_ + vel_;

	if (tr_.getY() < 0) {
		tr_.setY(0);
		vel_.setY(0);
	}
	else if (tr_.getY() + dim_.getY() > environment().height()) {
		tr_.setY(environment().height() - dim_.getY());
		vel_.setY(0);
	}

	if (tr_.getX() < 0) {
		tr_.setX(0);
		vel_.setX(0);
	}
	else if (tr_.getX() + dim_.getX() > environment().width()) {
		tr_.setX(environment().width() - dim_.getX());
		vel_.setX(0);
	}
}

void Tank::setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right)
{
	up_ = up;
	down_ = down;
	left_ = left;
	right_ = right;
}