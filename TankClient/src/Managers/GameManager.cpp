#include "GameManager.h"
#include "../Utils/Environment.h"

#include <cassert>

GameManager::GameManager(): scenerioLimits_(), relativeLimits_() {
}

GameManager::~GameManager() {
}

Vector2D GameManager::getScenerioLimits() {
	return scenerioLimits_;
}

Vector2D GameManager::getRelativeScenerioLimits() {
	return relativeLimits_;
}

void GameManager::setScenerioLimits(Vector2D limit) {
		scenerioLimits_ = limit;
		relativeLimits_ = Vector2D(Environment::instance()->width() - scenerioLimits_.getX(),Environment::instance()->height() - scenerioLimits_.getY());
}