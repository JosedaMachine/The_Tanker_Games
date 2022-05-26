#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundEffect.h"

#include "Transform.h"
#include "State.h"
#include "Heart.h"

class CollisionsManager : public Component {
public:
	CollisionsManager(SoundEffect* crash, SoundEffect* destroy) : 
		state_(nullptr), asteroidsManager_(nullptr), crash_sfx_(crash), destroy_sfx_(destroy) {}

	virtual ~CollisionsManager() {}

	void init() override {
		state_ = entity_->getComponent<State>();
		asteroidsManager_ = entity_->getComponent<AsteroidsManager>();

		assert(state_ != nullptr && asteroidsManager_ != nullptr);
	}

	void update() override {
		auto entities = entity_->getMngr()->getEntities();

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i]->hasGroup<Asteroid_grp>()) { // para cada asteroide
				auto asteroid = entities[i];
				auto asteroidTr_ = entities[i]->getComponent<Transform>();

				auto fighter = entity_->getMngr()->getHandler<Player_hdlr>();
				auto fighterTr_ = fighter->getComponent<Transform>();

				auto& pos = asteroidTr_->getPos();
				auto w = asteroidTr_->getW();
				auto h = asteroidTr_->getH();

				// comprobamos si colisiona con el caza
				if (Collisions::collides(pos, w, h, fighterTr_->getPos(), fighterTr_->getW(), fighterTr_->getH())) {
					// en caso de que colisione, quitamos una vida
					auto health = fighter->getComponent<Heart>();
					health->eraseLife();

					// reseteamos el numero de asteroides
					asteroidsManager_->resetNumAsteroids();

					// cambiamos el estado acorde al numero de vidas actual
					if (health->getLifes() > 0)
						state_->setState(states::PAUSED);
					else
						state_->setState(states::GAMEOVER);

					//desactivamos todas las entidades para su posterior eliminacion
					for (auto entity : entities)
						entity->setActive(false);

					//reactivamos caza y manager tras desactivar todas las entidades
					fighter->setActive(true);
					fighter->removeComponent<FighterCtrl>();
					fighter->removeComponent<Gun>();
					entity_->getMngr()->getHandler<Manager_hdlr>()->setActive(true);

					// recolocamos el caza y reseteamos su velocidad y rotacion
					fighterTr_->getPos().set(sdlutils().width() / 2.0f - (fighterTr_->getW() / 2),
						sdlutils().height() / 2.0f - (fighterTr_->getH() / 2));
					fighterTr_->getVel().set(Vector2D(0, 0));
					fighterTr_->setRot(0);
					
					// sonido de choque
					crash_sfx_->play();

					break; //salimos del bucle principal
				}
				else { // en caso de no colisionar con el caza
					for (int i = 0; i < entities.size(); i++) {
						// comprobamos si colisiona con alguna bala
						if (entities[i]->hasGroup<Bullet_grp>() && entities[i]->isActive()) {
							auto bulletTr_ = entities[i]->getComponent<Transform>();
							// si colisiona
							if (Collisions::collides(pos, w, h, bulletTr_->getPos(), bulletTr_->getW(), bulletTr_->getH())) {
								// aplicamos el comportamiento de colision correspondiente
								asteroidsManager_->onCollision(asteroid); 
								entities[i]->setActive(false); // desactivamos la bala
								destroy_sfx_->play(); // sonido de explosion de disparo
							}
						}
					}
				}
			}
		}
	}

private:
	State* state_;
	AsteroidsManager* asteroidsManager_;
	SoundEffect* crash_sfx_, *destroy_sfx_;
};
#endif