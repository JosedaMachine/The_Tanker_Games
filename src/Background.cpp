#include "Background.h"
#include <iostream>
#include "GameManager.h"
#include "Environment.h"

Background::Background() : GameObject(){
    GameManager::instance()->setScenerioLimits(Vector2D(Environment::instance()->width() - 21, Environment::instance()->height() - 66));
}

Background::~Background() {
}

void Background::update(){
	
}