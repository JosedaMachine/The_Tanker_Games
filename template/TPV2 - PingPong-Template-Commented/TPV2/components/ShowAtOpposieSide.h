#pragma once
#include <SDL.h>
#include <cassert>

#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "..//sdlutils/SDLUtils.h"

struct ShowAtOpposieSide : public Component {
public:
	ShowAtOpposieSide(Entity* entity, Manager* mngr, Vector2D winProps) :
		tr_(nullptr), windowProps(winProps), w(), h(), windowH(), windowW() {
		entity_ = entity;
		mngr_ = mngr;
		tr_ = mngr_->getComponent<Transform>(entity_);
		assert(tr_ != nullptr);

		//Guardamos la altura y anchura del jugador
		w = tr_->width_;
		h = tr_->height_;

		//Guardamos las propiedades de la ventana
		windowW = windowProps.getX();
		windowH = windowProps.getY();
	}
	virtual ~ShowAtOpposieSide() {
	}


	Transform* tr_;
	Entity* entity_;
	Manager* mngr_;
	Vector2D windowProps; //Para no tener que chequear en cada update
	float w, h, windowW, windowH;
};