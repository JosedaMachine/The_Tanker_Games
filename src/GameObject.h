// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once


#include <SDL2/SDL.h>

#include "Vector2D.h"


class GameObject {
public:
	GameObject() :
			pos_(), vel_(), width_(), height_() {
	}
	virtual ~GameObject() {
	}

	virtual void handleInput(const SDL_Event &event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	inline float getHeight() const {
		return height_;
	}

	inline void setHeight(float height) {
		height_ = height;
	}

	inline Vector2D& getPos() {
		return pos_;
	}

	inline Vector2D& getVel() {
		return vel_;
	}

	inline float getWidth() const {
		return width_;
	}

	inline void setWidth(float width) {
		width_ = width;
	}

protected:

	Vector2D pos_;
	Vector2D vel_;
	float width_;
	float height_;
};

