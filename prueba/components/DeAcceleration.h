#ifndef DEACCELERATION_H_
#define DEACCELERATION_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

#include "Transform.h"

class DeAcceleration : public Component
{
public:
	DeAcceleration() : tr_(nullptr) {};

	virtual ~DeAcceleration() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& vel = tr_->getVel();
		// aplicamos una desaceleracion a la velocidad en cada iteracion
		vel.set(vel * deAcceleration);
	}

private:
	Transform* tr_;
	const float deAcceleration = 0.995f;
};
#endif