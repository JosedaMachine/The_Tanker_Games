#include "FighterSystem.h"
#include "GameCtrlSystem.h"

#include "../ecs/Entity.h"

FighterSystem::FighterSystem() : playerFighter_(nullptr), fighterTr_(nullptr), opposieFighter_(nullptr){
	deacceleration_ = 0.95f;
}

FighterSystem::~FighterSystem(){
}

void FighterSystem::init(){

}

void FighterSystem::update(){

	//Si no se ha creado el player, no actualizamos
	if (playerFighter_ != nullptr && manager_->getSystem<GameCtrlSystem>()->getGameState() == GameState::RUNNING){
		assert(fighterTr_ != nullptr);
		auto& vel = fighterTr_->vel_;
		if (ih().keyDownEvent()) {

			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				//Avanza hacia arriba y rotamos el vector dirección para que apunte hacia donde apunta el caza
				vel = vel + Vector2D(0, -1).rotate(fighterTr_->rotation_) * 0.2f;
				sdlutils().soundEffects().at("thrust").play();
			}

			if (ih().isKeyDown(SDLK_LEFT)) {
				fighterTr_->rotation_ = (fighterTr_->rotation_ - 5.0f);
			}
			else if (ih().isKeyDown(SDLK_RIGHT)) {
				fighterTr_->rotation_ = (fighterTr_->rotation_ + 5.0f);
			}
		}

		if (vel.magnitude() >= 10.0f) vel = vel.normalize() * 10.0f;


		auto* opposieSide = manager_->getComponent<ShowAtOpposieSide>(manager_->getHandler<Player>());
		Vector2D pos = fighterTr_->pos_;
		//Guardamos las posici�n
		float x = pos.getX();
		float y = pos.getY();

		if (x > opposieSide->windowW)
			//Le restamos su anchura porque si no aparece autom�ticamente en pantalla	
			fighterTr_->pos_.setX(0 - opposieSide->w);
		else if (x < 0 - opposieSide->w) 	//Le restamos su anchura porque si no se trigerea en cuanto toca el borde
			fighterTr_->pos_.setX(opposieSide->windowW);
		else if (y < 0 - opposieSide->h)//Le restamos su altura porque si no aparece autom�ticamente en pantalla	
			fighterTr_->pos_.setY(opposieSide->windowH);
		else if (y > opposieSide->windowH + opposieSide->h)//Le sumamos su altura sporque si no se trigerea en cuanto toca el borde
			fighterTr_->pos_.setY(0 - opposieSide->h);

		//We move the position of the player depending on the velocity
		fighterTr_->pos_ = fighterTr_->pos_ + fighterTr_->vel_;

		//Each frame we deaccelerate the velocity of the player by the factor "deaccelertion"
		vel.set(vel.getX() * deacceleration_, vel.getY() * deacceleration_);
	}
}

void FighterSystem::createPlayer(){
	playerFighter_ = manager_->addEntity();

	Vector2D pos((float)sdlutils().width() / 2.0f - size / 2.0f, (float)sdlutils().height() / 2.0f - size / 2.0f);

	fighterTr_ = manager_->addComponent<Transform>(playerFighter_, pos, Vector2D(), size, size, 0.0f);
	opposieFighter_ = manager_->addComponent<ShowAtOpposieSide>(playerFighter_, playerFighter_, manager_, Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
	manager_->addComponent<Health>(playerFighter_);
	manager_->setHandler<Player>(playerFighter_);
}

void FighterSystem::onCollisionWithAsteroid(Entity* a){
	fighterTr_->pos_.set(sdlutils().width() / 2 - fighterTr_->width_ / 2.0f, sdlutils().height() / 2 - fighterTr_->height_ / 2.0f);
	fighterTr_->rotation_ = 0;
	fighterTr_->vel_.set(0.0f, 0.0f);
}
