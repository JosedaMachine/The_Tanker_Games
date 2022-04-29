// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionSystem.h"

#include <cassert>
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "BallSystem.h"
#include "GameManagerSystem.h"
#include "NetworkSystem.h"

CollisionSystem::CollisionSystem() :
		ballTr_(nullptr), //
		leftPaddelTr_(nullptr), //
		rightPaddelTr_(nullptr), //
		paddleHit_(nullptr) {

}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::init() {
	paddleHit_ = &sdlutils().soundEffects().at("paddle_hit");
	ballTr_ = manager_->getComponent<Transform>(manager_->getHandler<Ball>());
	assert(ballTr_ != nullptr);
	leftPaddelTr_ = manager_->getComponent<Transform>(
			manager_->getHandler<LeftPaddle>());
	assert(leftPaddelTr_ != nullptr);
	rightPaddelTr_ = manager_->getComponent<Transform>(
			manager_->getHandler<RightPaddle>());
	assert(rightPaddelTr_ != nullptr);
}

void CollisionSystem::update() {

	if (!manager_->getSystem<NetworkSystem>()->isMaster())
		return;

	if (manager_->getSystem<GameManagerSystem>()->getState()
			!= GameManagerSystem::RUNNING)
		return;

	// check if ball hits paddles
	if (Collisions::collides(leftPaddelTr_->pos_, leftPaddelTr_->width_,
			leftPaddelTr_->height_, ballTr_->pos_, ballTr_->width_,
			ballTr_->height_)
			|| Collisions::collides(rightPaddelTr_->pos_,
					rightPaddelTr_->width_, rightPaddelTr_->height_,
					ballTr_->pos_, ballTr_->width_, ballTr_->height_)) {

		// change the direction of the ball, and increment the speed
		ballTr_->vel_.setX(-ballTr_->vel_.getX());
		ballTr_->vel_ = ballTr_->vel_ * 1.2f;
		manager_->getSystem<NetworkSystem>()->sendBallInfo(ballTr_->pos_,
				ballTr_->vel_);

		// play some sound
		paddleHit_->play();

	} else if (ballTr_->pos_.getX() < 0) {
		manager_->getSystem<GameManagerSystem>()->onBallExit(
				GameManagerSystem::LEFT);
		manager_->getSystem<BallSystem>()->resetBall();
	} else if (ballTr_->pos_.getX() + ballTr_->width_ > sdlutils().width()) {
		manager_->getSystem<GameManagerSystem>()->onBallExit(
				GameManagerSystem::RIGHT);
		manager_->getSystem<BallSystem>()->resetBall();
	}

}
