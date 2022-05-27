// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameManager.h"

#include <cassert>
#include <string>

#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

GameManager::GameManager(GameObject *b, GameObject *left, GameObject *right) :
		score_(), //
		state_(NEWGAME), //
		maxScore_(5), //
		ball_(b), //
		leftPaddle_(left), //
		rightPaddle_(right) {
}

GameManager::~GameManager() {
}

void GameManager::handleInput(const SDL_Event &event) {
	if (state_ != RUNNING) {
		if (event.type == SDL_KEYDOWN
				&& event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			switch (state_) {
			case NEWGAME:
				moveBall();
				state_ = RUNNING;
				break;
			case PAUSED:
				moveBall();
				state_ = RUNNING;
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				score_[0] = score_[1] = 0;
				break;
			default:
				break;
			}
		}
	}
}

void GameManager::update() {
	if (state_ != RUNNING)
		return;

	// check if ball hits paddles
	if (Collisions::collides(leftPaddle_->getPos(), leftPaddle_->getWidth(),
			leftPaddle_->getHeight(), ball_->getPos(), ball_->getWidth(),
			ball_->getHeight())
			|| Collisions::collides(rightPaddle_->getPos(),
					rightPaddle_->getWidth(), rightPaddle_->getHeight(),
					ball_->getPos(), ball_->getWidth(), ball_->getHeight())) {

		// change the direction of the ball, and increment the speed
		auto &vel = ball_->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ball_->getPos().getX() < 0)
		onBallExit(LEFT);
	else if (ball_->getPos().getX() + ball_->getWidth() > sdlutils().width())
		onBallExit(RIGHT);
}

void GameManager::render() {

	// message when game is not running
	if (state_ != RUNNING) {

		// game over message
		if (state_ == GAMEOVER) {
			auto &t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state_ == NEWGAME) {
			auto &t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		} else {
			auto &t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
		}
	}

	// score
	Texture scoreMsg(
			sdlutils().renderer(), //
			std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
			sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}


void GameManager::onBallExit(Side side) {

	assert(state_ == RUNNING); // this should be called only when game is runnnig

	if (side == LEFT) {
		score_[1]++;
	} else {
		score_[0]++;
	}
	resetBall();
	if (score_[1] < maxScore_ && score_[1] < maxScore_)
		state_ = PAUSED;
	else
		state_ = GAMEOVER;
}

void GameManager::resetBall() {
	ball_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);
	ball_->getVel().set(0, 0);
}

void GameManager::moveBall() {
	auto &r = sdlutils().rand();

	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
	ball_->getVel().set(v.normalize() * 2);
}
