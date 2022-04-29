#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "..//sdlutils/SDLUtils.h"

enum States {NEWGAME, PAUSED, RUNNING, GAMEOVER};

struct State : public Component {
public:
	State() :
		s(NEWGAME), win(false) {
	}

	virtual ~State() {
	}


	States s;

	bool win;
}
;