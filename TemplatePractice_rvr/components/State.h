#ifndef STATE_H_
#define STATE_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

enum class states { NEWGAME, PAUSED, RUNNING, GAMEOVER, WIN };

class State : public Component {
public:
	State() : state_(states::NEWGAME) {}

	virtual ~State() {}

	states getState() { return state_; };

	void setState(states const st) { state_ = st; };

	void render() override {
		// si no esta en el estado de jugar, presenta un
		// mensaje acorde al estado actual
		if (state_ != states::RUNNING) {
			if (state_ == states::GAMEOVER) {
				auto& t = sdlutils().msgs().at("gameover");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
			else if (state_ == states::NEWGAME) {
				auto& t = sdlutils().msgs().at("start");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
			else if (state_ == states::PAUSED) {
				auto& t = sdlutils().msgs().at("continue");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
			else if (state_ == states::WIN) {
				auto& t = sdlutils().msgs().at("win");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
		}
	}

private:
	states state_;
};
#endif