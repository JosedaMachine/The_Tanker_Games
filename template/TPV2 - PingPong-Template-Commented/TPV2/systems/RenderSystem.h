#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../components/Transform.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	void init() override;

	// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego está parado (como en la
	// práctica 1)
	// - Otra posibilidad es definir un método render en la clase System, y distribuir
	// este código en los sistemas correspondientes en lugar de tener un sólo
	// sistema para rendering
	void update() override;

private:
	Texture* playerTexture, *bulletTexture;

	Entity* player;
	SDL_Rect dest;
};