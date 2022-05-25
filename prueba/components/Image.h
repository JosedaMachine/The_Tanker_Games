#ifndef IMAGE_H_
#define IMAGE_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture* tex) : tr_(nullptr), tex_(tex) {}

	virtual ~Image() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		//renderizamos la imagen acorde a su posicion y dimensiones
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
};
#endif