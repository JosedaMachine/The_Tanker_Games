#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Environment.h"
#include "GameObject.h"

Game::Game() {}

Game::~Game() {}

void Game::init(int w, int h)
{
    Environment::init("My Game", w, h);
}

void Game::run()
{
    bool close = false;
    SDL_Event event;

    // animation loop
    while (!close)
    {
        // handle input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
				close = true;
				continue;
			}
			
            for (auto &o : objs_) 
				o->handleInput(event);
		}

		// update
		for (auto &o : objs_)
			o->update();

		environment().clearRenderer();

		// render
		for (auto &o : objs_) {
			o->render();
		}

		environment().presentRenderer();
		// Uint32 frameTime = sdlutils().currRealTime() - startTime;

		// if (frameTime < 20)
		// 	SDL_Delay(20 - frameTime);
    }
}

void Game::shutdown() {
    for (unsigned int i = 0; i < objs_.size(); i++)
        delete objs_[i];
}