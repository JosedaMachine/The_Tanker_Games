#include "BulletsSystem.h"

BulletsSystem::BulletsSystem(){
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::init() {
}

void BulletsSystem::update() {
	//It could be done with a vector of bullets too...But we use groups
	for (Entity* bullet : manager_->getEnteties()) {
		if (manager_->hasGroup<Bullet_grp>(bullet)) {
			auto* tr_ = manager_->getComponent<Transform>(bullet);

			//Move the bullets
			tr_->pos_ = tr_->pos_ + tr_->vel_;

			
			auto& pos = tr_->pos_;
			auto& vel = tr_->vel_;
			auto w = tr_->width_;
			auto h = tr_->height_;
			//If the bullets are out of the window, we desactivate them
			if (pos.getX() < 0 || pos.getX() + w > sdlutils().width() || pos.getY() < 0 || pos.getY() + h > sdlutils().height()) {
				manager_->setActive(bullet, false);
			}
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {
	Entity* bullet = manager_->addEntity();
	manager_->addComponent<Transform>(bullet, pos, vel, width, height, vel.angle(Vector2D(0.0f, -1.0f)));
	manager_->setGroup<Bullet_grp>(bullet, true);
	sdlutils().soundEffects().at("fire").play();
}

void BulletsSystem::onCollisionWithAsteroid(Entity* bullet, Entity* a){
	manager_->setActive(bullet, false);
}
