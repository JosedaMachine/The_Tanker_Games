#pragma once
#include <cassert>

#include "..//components/DisableOnExit.h"
#include "../ecs/Component.h"
#include "../ecs/Manager.h"

struct Gun : public Component {
public:
	Gun(const float& t = 2000.0f) :
		tr_(nullptr), h(), w(), r(), lastTime(), timer(t), mngr(nullptr){}

	virtual ~Gun() {
	}



	Transform* tr_;
	Manager* mngr;
	float w, h, r, timer, lastTime;

};