// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

struct Transform;
class SoundEffect;

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void init() override;
	void update() override;
private:
	Transform *ballTr_;
	Transform *leftPaddelTr_;
	Transform *rightPaddelTr_;
	SoundEffect *paddleHit_;
};

