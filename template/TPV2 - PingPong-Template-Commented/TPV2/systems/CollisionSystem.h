#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include <vector>
#include "../ecs/Manager.h"

#include "../components/Health.h"
#include "../components/Transform.h"

class CollisionSystem : public System {
public:

	void init() override;

	// - si el juego está parado no hacer nada.
	// - comprobar colisiones como en la práctica 1 y avisar a los sistemas
	// correspondientes en caso de colisiones
	void update() override;


	/// <summary>
/// 
/// </summary>
/// <param name="t"></param>
/// <param name="other"></param>
/// <returns></returns>
	bool checkCollision(Transform* t, Transform* other);

	void actPlayerData();

private:
	std::vector<Entity*> entities_;

	Health* health_;
	Entity* player;
	Transform* playerT_;
};