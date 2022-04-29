#pragma once
#include <cassert>

#include "..//components/DisableOnExit.h"
#include "../ecs/Component.h"
#include"../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"


struct Health : public Component {
public:
	Health(Vector2D pos = Vector2D(0, 0), Vector2D size = Vector2D(50, 50), const int h = 3, Texture* tex_ = &sdlutils().images().at("heart")) :
		pos_(pos), size_(size), lives(h), initLives(lives), tex(tex_), mngr(nullptr) {
	}

	virtual ~Health() {
	}

	Vector2D pos_, iniPos_, size_;
	Texture* tex;
	Manager* mngr;
	int lives, initLives;
};