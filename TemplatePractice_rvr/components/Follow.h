#ifndef FOLLOW_H_
#define FOLLOW_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Follow : public Component {
public:
	Follow() : tr_(nullptr) {}

	virtual ~Follow() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		Transform* fighter_tr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
		auto& vel = tr_->getVel();
		// rotamos progresivamente a la izquierda o derecha dependiendo
		// de si el caza esta a su derecha o a su izquierda
		vel = vel.rotate(vel.angle(fighter_tr_->getPos() - tr_->getPos()) > 0 ? 1.0f : -1.0f);
	}

private:
	Transform* tr_;
};
#endif