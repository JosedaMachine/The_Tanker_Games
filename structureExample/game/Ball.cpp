// This file is part of the course TPV2@UCM - Samir Genaim

#include "Ball.h"

#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"

Ball::Ball() :
		Ball(build_sdlcolor(0xffffffff)) //
{
}

Ball::Ball(SDL_Color color) :
		color_(color) //
{
}

Ball::~Ball() {
}

void Ball::update() {
	pos_ = pos_ + vel_;

	// bounce on top/bottom borders
	if (pos_.getY() < 0) {
		pos_.setY(0.0f);
		vel_.setY(-vel_.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (pos_.getY() + height_ > sdlutils().height()) {
		pos_.setY(sdlutils().height() - height_);
		vel_.setY(-vel_.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}



}

void Ball::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

	SDL_Rect rect = build_sdlrect(pos_, width_, height_);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);
}

void Ball::handleInput(const SDL_Event&) {
}
