#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

struct DisableOnExit : public Component {
public:
	DisableOnExit(Manager* mngr, Entity* entity) :
		tr_(nullptr), entity_(entity) , mngr_(mngr){

		tr_ = mngr_->getComponent<Transform>(entity_);
		assert(tr_ != nullptr);
	}

	virtual ~DisableOnExit() {
	}



	Transform* tr_;
	Entity* entity_;
	Manager* mngr_;
};