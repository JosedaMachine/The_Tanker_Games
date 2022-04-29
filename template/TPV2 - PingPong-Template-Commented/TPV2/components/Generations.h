#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include"../sdlutils/SDLUtils.h"

struct Generations : public Component {
public:
	Generations(const int generations = 3): generations_(generations){
	}

	virtual ~Generations() {
	}

	int generations_;
};