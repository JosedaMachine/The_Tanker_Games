#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../components/Transform.h"
#include "../components/ShowAtOpposieSide.h"

#include "BulletsSystem.h"

class FighterGunSystem : public System
{
public:
	/// <summary>
	/// </summary>
	/// <param name="t">time in seconds</param>
	FighterGunSystem(const float& t = 0.95f);
	virtual ~FighterGunSystem();
	void init() override;

	// - si el juego está parado no hacer nada. Si el jugador pulsa SDLK_S, llamar
	// a shoot del BulletsSystem para añadir una bala al juego, etc.
	// - se puede incluir ese comportamiento en el FighterSystem directamente en
	// lugar de definirlo en un sistema separado
	void update() override;

	BulletsSystem* bulletSys;

private:
	Transform* fighterTr_;	
	float timer, lastTime;
};