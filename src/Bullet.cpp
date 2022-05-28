#include "Bullet.h"
#include "Environment.h"
#include <iostream>

Bullet::Bullet(Vector2D vel) : GameObject(), vel_(vel) {
    hola = true;
}

Bullet::~Bullet() {
        std::cout << "Borrada\n";
}

void Bullet::update()
{
    if(hola){
        std::cout << "Bala\n";
        hola = false;
    }

	if (vel_.magnitude() >= 10.0f) vel_ = vel_.normalize() * 10.0f;

	tr_ = tr_ + vel_;

	if (tr_.getY() + dim_.getY() < 0) {
        enabled_ = false;
	}
	else if (tr_.getY() > environment().height()) {
		enabled_ = false;
	}

	if (tr_.getX() + dim_.getX()< 0) {
		enabled_ = false;
	}
	else if (tr_.getX() > environment().width()) {
		enabled_ = false;
	}
}