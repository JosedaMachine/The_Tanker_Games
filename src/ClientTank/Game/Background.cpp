#include "Background.h"

#include "../Managers/GameManager.h"
#include "../SDL_Utils/Environment.h"

#include <iostream>

Background::Background() : GameObject(){
    GameManager::instance()->setScenerioLimits(Vector2D(Environment::instance()->width() - 21, Environment::instance()->height() - 66));
}

Background::~Background() {
}

void Background::update(){
	
}