// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Rotate : public Component {
public:
	Rotate() :
		tr_(nullptr), speed_(10.0) {
	}
	virtual ~Rotate() {
	}


	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}
	
	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDLK_LEFT)) {
				tr_->setRot(tr_->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDLK_RIGHT)) {
				tr_->setRot(tr_->getRot() + 5.0f);
			}
		}
	}

private:
	Transform* tr_;
	float speed_;
}
;

