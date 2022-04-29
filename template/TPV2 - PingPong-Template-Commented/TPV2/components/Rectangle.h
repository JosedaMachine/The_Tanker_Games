// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class Rectangle: public Component {
public:
	Rectangle() :
			Rectangle(build_sdlcolor(0xffffffff)) {
	}
	Rectangle(SDL_Color color) :
			color_(color), //
			tr_(nullptr) {
	}
	virtual ~Rectangle() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

	}
	void render() override {

		SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(color_));

		SDL_Rect rect = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());

		SDL_RenderFillRect(sdlutils().renderer(), &rect);

	}
private:
	SDL_Color color_;
	Transform *tr_;
};
