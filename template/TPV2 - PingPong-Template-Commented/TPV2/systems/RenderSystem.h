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

	// - dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego est� parado (como en la
	// pr�ctica 1)
	// - Otra posibilidad es definir un m�todo render en la clase System, y distribuir
	// este c�digo en los sistemas correspondientes en lugar de tener un s�lo
	// sistema para rendering
	void update() override;

private:
	Texture* playerTexture, *bulletTexture;

	Entity* player;
	SDL_Rect dest;
};