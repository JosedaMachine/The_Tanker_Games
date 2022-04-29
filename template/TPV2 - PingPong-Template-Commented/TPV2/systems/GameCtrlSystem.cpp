#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "CollisionSystem.h"





GameCtrlSystem::GameCtrlSystem() : hasWon_(false){
	state_ = GameState::NEWGAME;
}

GameCtrlSystem::~GameCtrlSystem()
{
}

void GameCtrlSystem::onFighterDeath(){

	for (Entity* enti : manager_->getEnteties())
		if (manager_->hasGroup<Asteroid_grp>(enti) || manager_->hasGroup<Bullet_grp>(enti)) manager_->setActive(enti, false);
}

void GameCtrlSystem::onAsteroidsExtinction(){
	for (Entity* enti : manager_->getEnteties()){

	}
}

GameState GameCtrlSystem::getGameState(){
	return state_;
}

void GameCtrlSystem::setState(GameState state){
	state_ = state;
}

void GameCtrlSystem::init(){
}

void GameCtrlSystem::update(){
	
	
	//Si no está corriendo escribimos mensaje
	if (state_ != GameState::RUNNING) {

		// game over message
		if (state_ == GameState::GAMEOVER) {
			//Mensaje si pierde
			if (!hasWon_) {
				message = &sdlutils().msgs().at("gameover");
			}//Mensaje si gana
			else {
				message = &sdlutils().msgs().at("win");
			}
		}
		// new game message
		else if (state_ == GameState::NEWGAME) {
			message = &sdlutils().msgs().at("start");
		}
		else {
			message = &sdlutils().msgs().at("continue");
		}
	}
	else{
		message = nullptr;
	}
	
	
	if (ih().keyDownEvent()) {
		//Si el jugador presiona la tecla espacio y no está jugando, cambia de estado 
		if (ih().isKeyDown(SDL_SCANCODE_SPACE) && state_ != GameState::RUNNING) {
			AsteroidsSystem* astSys = manager_->getSystem<AsteroidsSystem>();
			FighterSystem* fighterSys = manager_->getSystem<FighterSystem>();
			CollisionSystem* collisionSys = manager_->getSystem<CollisionSystem>();

			if (state_ == GameState::NEWGAME){
				fighterSys->createPlayer();

				astSys->startGame();

				collisionSys->actPlayerData();

				state_ = GameState::RUNNING;
			}
			else if (state_ == GameState::GAMEOVER && !hasWon_) {
				state_ = GameState::NEWGAME;
			}
			else {
				state_ = GameState::RUNNING;
				//Se instancian 10 asteroides posicionados aleatoriamente en los bordes de la pantalla
				astSys->startGame();
			}
		}
	}

}

bool& GameCtrlSystem::hasWon(){
	return hasWon_;
}

void GameCtrlSystem::setWin(bool t){
	hasWon_ = t;
}

Texture* GameCtrlSystem::getMessageTexture(){
	return message;
}
