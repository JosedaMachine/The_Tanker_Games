#include "GameObject.h"

#include <SDL2/SDL_image.h>

#include "Environment.h"
#include "macros.h"

GameObject::~GameObject() {
    if(text_ != nullptr)
        SDL_DestroyTexture(text_);
}

void GameObject::setTransform(const int x, const int y) {
    tr_.set(x, y);
}

void GameObject::setDimensions(const int w, const int h) {
    dim_.set(w, h);
}

Vector2D GameObject::getDimensions() const {
    return dim_;
}

void GameObject::setTexture(const std::string &path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
        throw "Couldn't load image: " + path;

    text_ = SDL_CreateTextureFromSurface(environment().renderer(), surface);
    if (text_ == nullptr) {
        SDL_FreeSurface(surface);
        throw "Couldn't load image: " + path;
    }

    textDim_.setX(surface->w);
    textDim_.setY(surface->h);

    SDL_FreeSurface(surface);
}

void GameObject::render()
{
    assert(text_ != nullptr);

    SDL_Rect src = build_sdlrect(0, 0, textDim_.getX(), textDim_.getY());
    SDL_Rect dest = build_sdlrect(tr_, dim_.getX(), dim_.getY());
    render(src, dest);
}

void GameObject::render(const SDL_Rect &src, const SDL_Rect &dest,
                const SDL_Point *p, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(environment().renderer(), text_, &src, &dest, rotation, p, flip);
}