#ifndef SHOW_AT_OPPOSITE_SIDE_H_
#define SHOW_AT_OPPOSITE_SIDE_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

class ShowAtOppositeSide : public Component
{
public:
	ShowAtOppositeSide() : tr_(nullptr) {};

	virtual ~ShowAtOppositeSide() {};

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& pos = tr_->getPos();

		//toroidal en el eje X (fluido)
		if (pos.getX() > sdlutils().width())
			pos.setX(0 - tr_->getW());
		else if(pos.getX() + tr_->getW() < 0)
			pos.setX(sdlutils().width());

		//toroidal en el eje Y (fluido)
		if (pos.getY() > sdlutils().height())
			pos.setY(0 - tr_->getH());
		else if (pos.getY() + tr_->getH() < 0)
			pos.setY(sdlutils().height());
	}

private:
	Transform* tr_;
};
#endif