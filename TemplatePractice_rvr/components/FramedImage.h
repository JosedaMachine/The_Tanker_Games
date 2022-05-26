#ifndef FRAMED_IMAGE_H_
#define FRAMED_IMAGE_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class FramedImage : public Component {
public:
	FramedImage(Texture* tex, int rows, int cols) : tr_(nullptr), tex_(tex), rows_(rows),
		cols_(cols), actRow_(0), actCol_(0), lastUpdate(0) {
		// guardamos ya ancho y alto en un SDL_Rect para reutilizarlo en renderizado
		auto w = tex->width() / cols;
		auto h = tex->height() / rows;
		src_ = { w * actCol_, h * actRow_, w, h };
	}

	virtual ~FramedImage() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		// cada vez que cambia de frame
		if (sdlutils().currRealTime() - lastUpdate > ms) {
			if (cols_ == actCol_ + 1) { // si ha llegado al final de la fila (nCols)
				// actualizamos la fila en caso de que sea el final o no
				actRow_ = (rows_ == actRow_ + 1 ? 0 : actRow_ + 1);
				actCol_ = 0; // reseteamos columna
			}
			else actCol_++;

			// actualizamos timer
			lastUpdate = sdlutils().currRealTime();
		}
	}

	void render() override {
		// calculamos el frame a renderizar
		src_.x = src_.w * actCol_;
		src_.y = src_.h * actRow_;

		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(src_, dest, tr_->getRot());
	}

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;

	int rows_, cols_;
	int actRow_, actCol_;
	const int ms = 50;
	int lastUpdate;
};
#endif