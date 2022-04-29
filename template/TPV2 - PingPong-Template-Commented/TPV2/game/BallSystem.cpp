// This file is part of the course TPV2@UCM - Samir Genaim

#include "BallSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "NetworkSystem.h"

BallSystem::BallSystem() :
		ballTr_(nullptr), //
		wallHit_(nullptr) {
}

BallSystem::~BallSystem() {
}

void BallSystem::init() {
	wallHit_ = &sdlutils().soundEffects().at("wall_hit");
	auto e = manager_->addEntity();
	ballTr_ = manager_->addComponent<Transform>(e);
	manager_->setHandler<Ball>(e);
	resetBall();
}

void BallSystem::update() {
	ballTr_->pos_ = ballTr_->pos_ + ballTr_->vel_;

	if (ballTr_->pos_.getY() < 0) {
		ballTr_->pos_.setY(0);
		ballTr_->vel_.setY(-ballTr_->vel_.getY());
		wallHit_->play();
	} else if (ballTr_->pos_.getY() + ballTr_->height_ > sdlutils().height()) {
		ballTr_->pos_.setY(sdlutils().height() - ballTr_->height_);
		ballTr_->vel_.setY(-ballTr_->vel_.getY());
		wallHit_->play();
	}
}

void BallSystem::resetBall() {
	ballTr_->vel_ = Vector2D();
	ballTr_->pos_ = Vector2D(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ballTr_->width_ = ballTr_->height_ = 11;
	manager_->getSystem<NetworkSystem>()->sendBallInfo(ballTr_->pos_,
			ballTr_->vel_);
}

void BallSystem::initBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));

	ballTr_->vel_.set(v.normalize() * 2);
	manager_->getSystem<NetworkSystem>()->sendBallInfo(ballTr_->pos_,
			ballTr_->vel_);
}

void BallSystem::setBallInfo(Vector2D pos, Vector2D vel) {
	ballTr_->vel_ = vel;
	ballTr_->pos_ = pos;
}
