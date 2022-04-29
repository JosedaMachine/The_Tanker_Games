#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/Health.h"


class FighterSystem : public System
{
public:
	FighterSystem();

	virtual ~FighterSystem();

	// - crear la entidad del caza, a�adir sus componentes (Transform, Health, etc.)
	// y asociarla con el handler correspondiente.
	void init() override;

	// - si el juego est� parado no hacer nada.
	// - actualizar la velocidad del caza y moverlo como en la pr�ctica 1.
	void update() override;

	// - Crea un jugador
	void createPlayer();

	// - poner el caza en el centro con velocidad 0 y rotaci�n 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego est� parado en RenderSystem).
	// - avisar al GameCtrlSystem que se ha muerto el caza (se puede tambi�n avisar
	// directamente en el CollisionSystem)
	void onCollisionWithAsteroid(Entity* a);

private:
	Entity* playerFighter_;
	Transform* fighterTr_;
	ShowAtOpposieSide* opposieFighter_;
	float deacceleration_; 
	float size = 50.0f;
};