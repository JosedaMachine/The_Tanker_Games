#ifndef FIGHTER_CTRL_H_
#define FIGHTER_CTRL_H_

#include <SDL2/SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"

#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl(SoundEffect* sfx) : tr_(nullptr), speed_(1.0f), thrust_sfx_(sfx) {}

	virtual ~FighterCtrl() {}

	inline void setSpeed(float speed) { speed_ = speed; }

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDL_SCANCODE_UP)) { // impulso
				auto& vel = tr_->getVel();
				auto newVel = vel + (Vector2D(0, -1).rotate(tr_->getRot())).normalize() * thrust;
				// si se pasa del limite de veocidad, establecemos este como nueva velocidad
				vel.set((newVel.magnitude() > speedLimit) ? 
					(Vector2D(0, -1).rotate(tr_->getRot())).normalize() * speedLimit : newVel);

				thrust_sfx_->play(); // sonido de impulso
			}
			else if (ih().isKeyDown(SDL_SCANCODE_LEFT)) { // rotacion izquierda
				tr_->setRot(tr_->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) { // rotacion derecha
				tr_->setRot(tr_->getRot() + 5.0f);
			}
		}
	}

private:
	Transform* tr_;
	SoundEffect* thrust_sfx_;

	const float thrust = 0.2f, speedLimit = 3.0f;
	float speed_;
};
#endif