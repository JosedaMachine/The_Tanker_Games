#include "Tank.h"

#include "Bullet.h"

#include "Environment.h"
#include "GameManager.h"

Tank::Tank(std::vector<GameObject *>* objs_) : GameObject(), vel_(), speed_(0) , deacceleration_(0.5) {
	gameObjs_ = objs_;
}

Tank::~Tank() {}

void Tank::handleInput(const SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN){
		if (e.key.keysym.scancode == up_)
			vel_ = vel_ + Vector2D(0, -1).rotate(rotation) * speed_;
		else if (e.key.keysym.scancode == down_)
			vel_ = vel_ + Vector2D(0, 1).rotate(rotation) * 0.7f *speed_;
		
		if (e.key.keysym.scancode == left_)
			rotation = (rotation - 5.0f);
		else if (e.key.keysym.scancode == right_)
			rotation = (rotation + 5.0f);

		if(e.key.keysym.scancode == shoot_){
			shoot();
		}
	}
}

void Tank::update()
{
	if (vel_.magnitude() >= 10.0f) vel_ = vel_.normalize() * 10.0f;

	tr_ = tr_ + vel_;

	if (tr_.getY() < GameManager::instance()->getRelativeScenerioLimits().getY()) {
		tr_.setY(GameManager::instance()->getRelativeScenerioLimits().getY());
		vel_.setY(0);
	}
	else if (tr_.getY() + dim_.getY() > GameManager::instance()->getScenerioLimits().getY()) {
		tr_.setY(GameManager::instance()->getScenerioLimits().getY() - dim_.getY());
		vel_.setY(0);
	}

	if (tr_.getX() < GameManager::instance()->getRelativeScenerioLimits().getX()) {
		tr_.setX(GameManager::instance()->getRelativeScenerioLimits().getX());
		vel_.setX(0);
	}
	else if (tr_.getX() + dim_.getX() > GameManager::instance()->getScenerioLimits().getX()) {
		tr_.setX(GameManager::instance()->getScenerioLimits().getX() - dim_.getX());
		vel_.setX(0);
	}

	vel_.set(vel_.getX() * deacceleration_, vel_.getY() * deacceleration_);
}

void Tank::setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode shoot)
{
	up_ = up;
	down_ = down;
	left_ = left;
	right_ = right;
	shoot_ = shoot;
}

void Tank::shoot() {

	Vector2D vel = Vector2D(0.0f, -1.0f).rotate(rotation) * (vel_.magnitude() + 5.0f);
	Bullet* bullet = new Bullet(vel);
	float w = dim_.getX();
	float h = dim_.getY();
	bullet->setDimensions(10, 10);

	Vector2D pos = tr_ + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 12.0f).rotate(rotation) - Vector2D(0, 10.0f);


	bullet->setTransform(pos.getX(), pos.getY());
	bullet->setTexture("./resources/images/bullet.png");
	gameObjs_->push_back(bullet);
}