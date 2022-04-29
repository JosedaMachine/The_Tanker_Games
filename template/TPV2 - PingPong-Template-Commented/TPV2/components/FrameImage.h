// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Transform.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

struct FrameImage : public Component {
public:
	FrameImage(Texture* tex, int rows, int cols, int r, int c, const float frameRate = 50.0f) :
		tr_(nullptr), //
		tex_(tex), //
		timer(frameRate) 
	{
		//ancho de cada sprite, //alto de cada sprite
		sizeXF = tex_->width() / cols;
		sizeYF = tex_->height() / rows;

		//Rectangulo base
		src_ = { sizeXF * c, sizeYF * r, sizeXF, sizeYF };

		posX = c;
		posY = r;
		iniPos = Vector2D((float)posX, (float)posY);
		wholeSize = Vector2D((float)cols, (float)rows);

		lastTime = sdlutils().currRealTime() - timer;
	}

	virtual ~FrameImage() {
	}

	Transform* tr_;
	Texture* tex_;
	Vector2D wholeSize, iniPos;
	SDL_Rect src_;

	float timer, lastTime;
	int sizeXF, sizeYF, posX, posY;
};
