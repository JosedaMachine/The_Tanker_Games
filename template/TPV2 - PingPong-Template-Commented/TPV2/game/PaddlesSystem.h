// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

struct Entity;

class PaddlesSystem: public System {
public:
	PaddlesSystem();
	virtual ~PaddlesSystem();
	void init() override;
	void update() override;

	// used to set the paddle position of the other layer
	void setPaddlePosition(Uint8 id, Vector2D pos);
private:
	void movePaddle(Entity *e);

	Entity *leftPaddle_;
	Entity *rightPaddle_;
};

