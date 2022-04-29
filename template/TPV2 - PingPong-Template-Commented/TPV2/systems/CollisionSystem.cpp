#include "CollisionSystem.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"
#include "FighterSystem.h"
#include "GameCtrlSystem.h"

#include "../utils/Collisions.h"


void CollisionSystem::init(){

}

void CollisionSystem::update(){
	entities_ = manager_->getEnteties();
	for (Entity* e : entities_) {
		//If the bullet collide with an asteroid
		if (manager_->hasGroup<Asteroid_grp>(e)){
			auto* t = manager_->getComponent<Transform>(e);
			for (Entity* bala : entities_) {
				if (manager_->hasGroup<Bullet_grp>(bala)) {
					auto* balaT = manager_->getComponent<Transform>(bala);
					if (checkCollision(t, balaT)) {
						auto* bulletSys = manager_->getSystem<BulletsSystem>();
						auto* asteroidSys = manager_->getSystem<AsteroidsSystem>();
						bulletSys->onCollisionWithAsteroid(bala, e);
						asteroidSys->onCollisionWithBullet(e, bala);
					}
				}
			}
		
			//Por si el jugador choca con un asteroide
			if (checkCollision(t, playerT_)) {
				health_->lives--;
				sdlutils().soundEffects().at("explosion").play();
				auto* fithter = manager_->getSystem<FighterSystem>();
				fithter->onCollisionWithAsteroid(e);

				auto* gameCtrSys = manager_->getSystem<GameCtrlSystem>();
				if (health_->lives > 0) {
					gameCtrSys->setState(GameState::PAUSED);
				}
				else {
					//state_->setStates(GAMEOVER);
					gameCtrSys->setState(GameState::GAMEOVER);
					health_->lives = health_->initLives;
					manager_->setActive(player, false);
				}

				auto* gameSys = manager_->getSystem<GameCtrlSystem>();
				//Ponemos al jugadro donde debe estar
				gameSys->onFighterDeath();
			}
		}
	}
	entities_ = manager_->getEnteties();
}

bool CollisionSystem::checkCollision(Transform* t, Transform* other){
	return (Collisions::collidesWithRotation(t->pos_, t->width_, t->height_, t->rotation_,
		other->pos_, other->width_, other->height_, other->rotation_));
}

void CollisionSystem::actPlayerData(){
	player = manager_->getHandler<Player>();
	playerT_ = manager_->getComponent<Transform>(player);
	health_ = manager_->getComponent<Health>(player);
}
