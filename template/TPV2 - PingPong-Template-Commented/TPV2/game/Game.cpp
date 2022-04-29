// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "BallSystem.h"
#include "CollisionSystem.h"
#include "GameManagerSystem.h"
#include "NetworkSystem.h"
#include "PaddlesSystem.h"
#include "RenderSystem.h"

Game::Game() {
	mngr_.reset(new Manager());
	networkSys_ = nullptr;
	ballSys_ = nullptr;
	paddlesSys_ = nullptr;
	collisionSys_ = nullptr;
	gameMngrSys_ = nullptr;
	renderSys_ = nullptr;
}

Game::~Game() {
}

void Game::init(const char *host, Uint16 port) {

	// ask the player for a name
	std::string playerName;
	std::cout << "Sir, enter you name: ";
	std::cin >> playerName;

	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	networkSys_ = mngr_->addSystem<NetworkSystem>(host, port, playerName);
	ballSys_ = mngr_->addSystem<BallSystem>();
	paddlesSys_ = mngr_->addSystem<PaddlesSystem>();
	collisionSys_ = mngr_->addSystem<CollisionSystem>();
	gameMngrSys_ = mngr_->addSystem<GameManagerSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || event.type == SDL_QUIT) {
			exit = true;
			continue;
		}

		mngr_->refresh();

		ballSys_->update();
		paddlesSys_->update();
		collisionSys_->update();
		gameMngrSys_->update();
		networkSys_->update();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

