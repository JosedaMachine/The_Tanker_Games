// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class CollideBounds: public Component {
public:
	CollideBounds() :
			tr_(nullptr) {
	}
	virtual ~CollideBounds() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto &pos = tr_->getPos();
		auto &vel = tr_->getVel();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() < 0){
			pos.setX(0.0);
		} else if (pos.getX() + w > sdlutils().width()) {
			pos.setX(sdlutils().width() - w);
		}

		if (pos.getY() < 0) {
			pos.setY(0.0);
		} else if (pos.getY() + h > sdlutils().height()) {
			pos.setY(sdlutils().height() - h);
		}
	}

private:
	Transform *tr_;
};

