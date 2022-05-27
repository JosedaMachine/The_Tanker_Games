#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <cassert>

#include <SDL2/SDL.h>

#include "Vector2D.h"

class GameObject {
public:
	GameObject() : tr_(), dim_(), text_(nullptr) {}

	virtual ~GameObject() {}

	virtual void handleInput(const SDL_Event &event) = 0;
	virtual void update() = 0;

	void render();

	void setTexture(const std::string& path);

	inline Vector2D& getTransform() {
		return tr_;
	}

	inline Vector2D& getDimensions() {
		return dim_;
	}

	inline SDL_Texture* getTexture() {
		return text_;
	}

protected:

	Vector2D tr_;
	Vector2D dim_;

	float rotation;

	SDL_Texture* text_;
	Vector2D textDim_;
    
	void render(const SDL_Rect &src, const SDL_Rect &dest,
            const SDL_Point *p = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
#endif