#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"

#include "BulletsSystem.h"

class AsteroidsSystem : public System
{
public:
	AsteroidsSystem(const int numAsteroids_ = 10, const int t_ = 10000, const float w = 20.0f, const float h = 20.0f);
	virtual ~AsteroidsSystem();

	void init() override;

	// - si el juego está parado no hacer nada.
	// - mover los asteroides como en la práctica 1.
	void update() override;

	// - Comienza el jugo
	void startGame();

	// - Divide un asteroide
	void divide(bool golden, const int& generations, Entity* ent);

	/// <summary>
	/// Crea un asteroide alrededor de los bordes de la pantalla
	/// </summary>
	/// <param name="nGenerations">Número de generaciones disponibles iniciales</param>
	void addAsteroids(int nGenerations = sdlutils().rand().nextInt(1, 4));

	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	// - pasamos una referencia a la bala aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// bala, etc.)
	// - si no hay más asteroides avisar al GameCtrlSystem
	void onCollisionWithBullet(Entity* a, Entity* b);

	//- Devuelve el número de asteroides que quedan
	int getGenerations();

private:

	Vector2D* playerPos;

	std::size_t numAsteroids;

	int generations_;
	float timer, lastTime; 
	float widthAst_, heightAst_;
};