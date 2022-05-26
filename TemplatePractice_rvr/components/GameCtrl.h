#ifndef GAME_CTRL_H_
#define GAME_CTRL_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

#include "State.h"
#include "AsteroidsManager.h"
#include "Heart.h"
#include "FighterCtrl.h"
#include "Gun.h"

class GameCtrl : public Component {
public:
	GameCtrl() : state_(nullptr), asteroidsMngr_(nullptr) {}

	virtual ~GameCtrl() {}

	void init() override {
		state_ = entity_->getComponent<State>();
		asteroidsMngr_ = entity_->getComponent<AsteroidsManager>();

		assert(state_ != nullptr && asteroidsMngr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			// si, estando fuera de juego, le da a espacio
			if (ih().isKeyDown(SDL_SCANCODE_SPACE) && state_->getState() != states::RUNNING) {
				// cambiamos a estado RUNNING o NEWGAME dependiendo de si estamos en
				// un estado final (WIN, GAMEOVER) o no (NEWGAME, PAUSED)
				state_->setState(state_->getState() > states::RUNNING ? states::NEWGAME : states::RUNNING);

				// si pasamos a RUNNING, generamos los 10 asteroides y reseteamos el timer de spawn de los asteroides
				if (state_->getState() == states::RUNNING) {
					for (int i = 0; i < 10; i++)
						asteroidsMngr_->generateAsteroid();
					// a�adimos estos componenetes solo al pasar al estado running para que el jugador no se 
					// mueva durante el resto de estados
					entity_->getMngr()->getHandler<Player_hdlr>()->addComponent<FighterCtrl>(&sdlutils().soundEffects().at("thrust"));
					entity_->getMngr()->getHandler<Player_hdlr>()->addComponent<Gun>(&sdlutils().soundEffects().at("fire"));
		
					asteroidsMngr_->resetTimer();
				}

				// si pasamos a NEWGAME, reseteamos las vidas del caza
				else if (state_->getState() == states::NEWGAME)
					entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Heart>()->resetLifes();
			}
		}
	}

private:
	State* state_;
	AsteroidsManager* asteroidsMngr_;
};
#endif