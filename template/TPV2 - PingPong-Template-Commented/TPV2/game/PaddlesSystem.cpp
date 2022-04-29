// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddlesSystem.h"

#include "../components/PaddleCtrlKeys.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "NetworkSystem.h"


PaddlesSystem::PaddlesSystem() :
		leftPaddle_(nullptr), //
		rightPaddle_(nullptr) {
}

PaddlesSystem::~PaddlesSystem() {
}

void PaddlesSystem::init() {
	leftPaddle_ = manager_->addEntity();
	manager_->addComponent<Transform>(leftPaddle_, //
			Vector2D(10.0, sdlutils().height() / 2.0f - 25.0f), //
			Vector2D(), //
			10.0f, 50.0f, 0.0f);
	manager_->addComponent<PaddleCtrlKeys>(leftPaddle_, //
			SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE, 5.0f);
	manager_->setHandler<LeftPaddle>(leftPaddle_);

	rightPaddle_ = manager_->addEntity();
	manager_->addComponent<Transform>(
			rightPaddle_, //
			Vector2D(sdlutils().width() - 10.0f - 10.0f,
					sdlutils().height() / 2.0f - 25.0f), //
			Vector2D(), //
			10.0f, 50.0f, 0.0f);
	manager_->addComponent<PaddleCtrlKeys>(rightPaddle_, //
			SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE, 5.0f);
	manager_->setHandler<RightPaddle>(rightPaddle_);
}

void PaddlesSystem::update() {

	// move you paddle only
	Uint8 myId = manager_->getSystem<NetworkSystem>()->getId();

	if (myId == 0)
		movePaddle(leftPaddle_);
	else
		movePaddle(rightPaddle_);
}

void PaddlesSystem::movePaddle(Entity *e) {

	auto tr_ = manager_->getComponent<Transform>(e);
	auto keys = manager_->getComponent<PaddleCtrlKeys>(e);

	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(keys->up_)) {
			tr_->vel_.setY(-keys->speed_);
		} else if (ih().isKeyDown(keys->down_)) {
			tr_->vel_.setY(keys->speed_);
		} else if (ih().isKeyDown(keys->stop_)) {
			tr_->vel_.setY(0.0f);
		}
	}

	tr_->pos_ = tr_->pos_ + tr_->vel_;

	if (tr_->pos_.getY() < 0) {
		tr_->pos_.setY(0);
		tr_->vel_.setY(0);
	} else if (tr_->pos_.getY() + tr_->height_ > sdlutils().height()) {
		tr_->pos_.setY(sdlutils().height() - tr_->height_);
		tr_->vel_.setY(0);
	}

	manager_->getSystem<NetworkSystem>()->sendPaddlePosition(tr_->pos_);

}

void PaddlesSystem::setPaddlePosition(Uint8 id, Vector2D pos) {
	Entity *e = nullptr;
	if (id == 0) {
		e = leftPaddle_;
	} else {
		e = rightPaddle_;
	}
	auto tr_ = manager_->getComponent<Transform>(e);
	tr_->pos_ = pos;
}
