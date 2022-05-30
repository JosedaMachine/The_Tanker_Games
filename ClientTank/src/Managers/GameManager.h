#ifndef GameManager_H
#define GameManager_H

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../SDL_Utils/Singleton.h"
#include "../SDL_Utils/RandomNumberGenerator.h"
#include "../SDL_Utils/macros.h"


class GameManager: public Singleton<GameManager> {

	friend Singleton<GameManager> ; // needed to give access to private constructors

public:

	virtual ~GameManager();

	// cannot copy/move
	GameManager(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	// the window's width
	Vector2D getScenerioLimits();

	Vector2D getRelativeScenerioLimits();
	
	void setScenerioLimits(Vector2D limit);


private:
	GameManager();
	Vector2D scenerioLimits_;
	Vector2D relativeLimits_;
};
#endif

// This macro defines a compact way for using the singleton GameManager, instead of
// writing GameManager::instance()->method() we write GameManager().method()
//
inline GameManager& GameManager() {
	return *GameManager::instance();
}