#ifndef HEART_H_
#define HEART_H_

#include "../ecs/Component.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"

class Heart : public Component {
public:
	Heart(Texture* text) : text_(text), lifes_(maxLifes_) {};

	virtual ~Heart() {};

	inline void eraseLife() { lifes_--; }

	inline void resetLifes() { lifes_ = maxLifes_; }

	inline int getLifes() { return lifes_; }

	void render() override {
		// renderizamos el numero de corazones en 
		// pantalla acorde a las vidas actuales del caza
		Vector2D pos = Vector2D(0, 0);
		for (int i = 0; i < lifes_; i++) {
			pos.setX((heartSize + 5) * i); // dejamos un peque�o margen entre corazones 
			SDL_Rect dest = build_sdlrect(pos, heartSize, heartSize);
			text_->render(dest, 0);
		}
	}

private:
	Texture* text_;

	const int maxLifes_ = 3, heartSize = 30;
	int lifes_;
};
#endif