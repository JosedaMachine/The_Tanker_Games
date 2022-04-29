// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <array>

#include "../ecs/System.h"

struct Transform;

class GameManagerSystem: public System {
public:

	enum GameSate : Uint8 {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	enum Side {
		LEFT = 0, //
		RIGHT
	};


	GameManagerSystem();
	virtual ~GameManagerSystem();

	Uint8 getState() {
		return state_;
	}

	const auto& getScore() {
		return score_;
	}

	void onBallExit(Side side);
	void onFighterDestroy(int id);
	void startGame();
	void changeState(Uint8 state, Uint8 left_score, Uint8 right_score);
	void resetGame();
	void init() override;
	void update() override;

private:
	std::array<Uint8, 2> score_;
	Uint8 state_;
	Uint8 maxScore_;
};

