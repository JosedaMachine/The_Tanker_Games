// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>
#include "GameObject.h"

class GameManager: public GameObject {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};
	
	enum GameSate {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManager(GameObject *b, GameObject *left, GameObject *right);
	virtual ~GameManager();

	void handleInput(const SDL_Event &event) override;
	void update() override;
	void render() override;

private:
	void onBallExit(Side side);
	void resetBall();
	void moveBall();
	std::array<unsigned int, 2> score_;
	GameSate state_;
	const unsigned int maxScore_;
	GameObject *ball_;
	GameObject *leftPaddle_;
	GameObject *rightPaddle_;
};

