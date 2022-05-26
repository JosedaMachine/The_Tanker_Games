#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

class DisableOnExit : public Component
{
public:
	DisableOnExit() : tr_(nullptr) {};

	virtual ~DisableOnExit() {};

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& pos = tr_->getPos();

		// si se sale del marco de juego por alguno de sus limites, desactivamos el objeto
		if (pos.getX() > sdlutils().width() || pos.getX() + tr_->getW() < 0 ||
			pos.getY() > sdlutils().height() || pos.getY() + tr_->getH() < 0)
			entity_->setActive(false);
	}

private:
	Transform* tr_;
};