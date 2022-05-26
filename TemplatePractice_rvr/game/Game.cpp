#include "Game.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Image.h"
#include "../components/Heart.h"
#include "../components/FighterCtrl.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../components/State.h"
#include "../components/GameCtrl.h"
#include "../components/AsteroidsManager.h"
#include "../components/CollisionsManager.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {}

void Game::init() {

	SDLUtils::init("Asteroid", 800, 600,
		"resources/config/resources.json");

	// FigtherCtrl y Gun se a�aden en GameCtrl.h, para controlar que solo lo tenga
	// durante el estado de juego (ver implementacion del update de GameCtrl.h [41-42],
	// update de CollisionManager.h [61-62] y onCollision de AsteroidsManager.cpp [84-85])
	auto* fighter = mngr_->addEntity();
	mngr_->setHandler<Player_hdlr>(fighter);
	fighter->addComponent<Transform>(Vector2D(sdlutils().width() / 2.0f - 25.0f, sdlutils().height() / 2.0f - 25.0f),
		Vector2D(), 50.0f, 50.0f, 0.0f);
	fighter->addComponent<DeAcceleration>();
	fighter->addComponent<Image>(&sdlutils().images().at("fighter"));
	fighter->addComponent<Heart>(&sdlutils().images().at("heart"));
	fighter->addComponent<ShowAtOppositeSide>();

	auto* gmManager = mngr_->addEntity();
	mngr_->setHandler<Manager_hdlr>(gmManager);
	gmManager->addComponent<State>();
	gmManager->addComponent<AsteroidsManager>();
	gmManager->addComponent<GameCtrl>();
	gmManager->addComponent<CollisionsManager>(&sdlutils().soundEffects().at("explosion"), &sdlutils().soundEffects().at("bang"));
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

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}