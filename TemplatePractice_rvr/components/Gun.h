#ifndef GUN_H_
#define GUN_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundEffect.h"

#include "Transform.h"
#include "Image.h"
#include "DisableOnExit.h"

class Gun : public Component
{
public:
	Gun(SoundEffect* sfx) : tr_(nullptr), bullet_sfx_(sfx), msToNextBullet(0) {};

	virtual ~Gun() { }

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	// se crea una bala cuando se pulsa la s 
	void update() override {
		if (sdlutils().currRealTime() - msToNextBullet > nextBullet) {
			if (ih().isKeyDown(SDL_SCANCODE_S)) {
				createBullet();
				bullet_sfx_->play();
				msToNextBullet = sdlutils().currRealTime();
			}
		}
	}

private:
	Transform* tr_;
	SoundEffect* bullet_sfx_;

	const float bulletH = 20.0f, bulletW = 5.0f;
	const int nextBullet = 250;
	int msToNextBullet; // cooldown hasta la siguiente bala

	void createBullet();
};
#endif