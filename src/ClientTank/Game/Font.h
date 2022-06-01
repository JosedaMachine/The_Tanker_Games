#ifndef FONT_H
#define FONT_H

#include <string>
#include <cassert>
#include <iostream>

#include <SDL2/SDL_ttf.h>

#include "../SDL_Utils/GameObject.h"
#include "../SDL_Utils/macros.h"

class Font: public GameObject {
public:
	Font(const std::string &fileName, const std::string t, SDL_Color c, int size) {
		font_ = TTF_OpenFont(fileName.c_str(), size);
		if (font_ == nullptr) {
			throw "Couldn't load font: " + fileName;
		}

		text_ = t;
		color_ = c;

		t_ = SDL_CreateTextureFromSurface(environment().renderer(), TTF_RenderUTF8_Solid(font_, text_.c_str(), color_));
	}

	virtual ~Font() {
		if (font_ != nullptr)
			TTF_CloseFont(font_);
		if(t_ != nullptr)
        	SDL_DestroyTexture(t_);
	}

	virtual void render() {
		assert(font_ != nullptr);

	    SDL_Rect dest = build_sdlrect(tr_, dim_.getX(), dim_.getY());
		SDL_RenderCopy(environment().renderer(), t_, nullptr, &dest);
	}

private:

	TTF_Font *font_;
	SDL_Texture* t_;

	std::string text_;
	SDL_Color color_;
};
#endif