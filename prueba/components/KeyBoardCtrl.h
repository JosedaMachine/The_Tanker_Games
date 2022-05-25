#ifndef KEYBOARD_CTRL_H_
#define KEYBOARD_CTRL_H_

#include <SDL2/SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

#include "Transform.h"

class KeyBoardCtrl: public Component {
public:
	KeyBoardCtrl() : tr_(nullptr), speed_(10.0) {}

	virtual ~KeyBoardCtrl() {}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto &vel = tr_->getVel();
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				vel.setY(-speed_);
			} else if (ih().isKeyDown(SDL_SCANCODE_DOWN)) {
				vel.setY(speed_);
			} else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				vel.setX(-speed_);
			} else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				vel.setX(speed_);
			} else if (ih().isKeyDown(SDL_SCANCODE_STOP)) {
				vel.setY(0.0f);
			}
		}
	}

private:
	Transform *tr_;
	float speed_;
};
#endif