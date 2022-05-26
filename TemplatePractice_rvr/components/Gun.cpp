#include "Gun.h"

// metodo que crea una bala con sus componentes necesarios
void Gun::createBullet() {
	auto bullet = entity_->getMngr()->addEntity();

	// creamos la bala con la rotacion del caza en su posicion correspondiente
	Vector2D bPos = (tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2)) -
		Vector2D(0.0f, bulletH / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot())
		- Vector2D(2.0f, 10.0f);
	// aplicamos la velocidad con la misma rotacion del caza
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);

	bullet->addComponent<Transform>(bPos, bVel, bulletW, bulletH, tr_->getRot());
	bullet->addComponent<Image>(&sdlutils().images().at("fire"));
	bullet->addComponent<DisableOnExit>();
	bullet->setGroup<Bullet_grp>(bullet);
}