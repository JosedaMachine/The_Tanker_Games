#include "GameObject.h"

#include <SDL2/SDL_image.h>

#include "macros.h"

void GameObject::setTexture(const std::string &path) {
    // SDL_Surface *surface = IMG_Load(fileName.c_str());
    // if (surface == nullptr)
    //     throw "Couldn't load image: " + path;

    // text_ = SDL_CreateTextureFromSurface(renderer, surface);
    // if (text_ == nullptr) {
    //     SDL_FreeSurface(surface);
    //     throw "Couldn't load image: " + path;
    // }

    // textDim_.setX(surface->w);
    // textDim_.setY(surface->h);
}

void GameObject::render()
{
    // assert(text_ != nullptr);

    // SDL_Rect src = build_sdlrect({ 0, 0 }, textDim_.getX(), textDim_.getY());
    // SDL_Rect dest = build_sdlrect(tr_, dim_.getX(), dim_.getY());
    // render(src, dest);
}

void GameObject::render(const SDL_Rect &src, const SDL_Rect &dest,
                const SDL_Point *p, SDL_RendererFlip flip)
{
    // SDL_RenderCopyEx(rnd, text_, &src, &dest, rotation, p, flip);
}