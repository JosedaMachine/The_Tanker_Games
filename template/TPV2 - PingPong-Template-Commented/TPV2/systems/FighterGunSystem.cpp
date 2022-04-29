#include "FighterGunSystem.h"
#include "GameCtrlSystem.h"



FighterGunSystem::FighterGunSystem(const float& t): fighterTr_(nullptr), timer(t * 1000.0f){
}

FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::init(){
	lastTime = sdlutils().currRealTime() - timer;

}

void FighterGunSystem::update() {
	//Todo el checkeo de input
	if (ih().keyDownEvent()) {
		if ((manager_->getSystem<GameCtrlSystem>()->getGameState() == GameState::RUNNING) && ih().isKeyDown(SDL_SCANCODE_S)) {
			if (sdlutils().currRealTime() - lastTime > timer){
				fighterTr_ = manager_->getComponent<Transform>(manager_->getHandler<Player>());

				lastTime = sdlutils().currRealTime();
				bulletSys = manager_->getSystem<BulletsSystem>();

				double w = fighterTr_->width_;
				double h = fighterTr_->height_;
				double r = fighterTr_->rotation_;
				Vector2D bPos = fighterTr_->pos_ + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
				float auxVel = fighterTr_->vel_.magnitude();
				Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (auxVel + 5.0f);
				bulletSys->shoot(bPos, bVel, 5.0f, 20.0f);
			}
		}
	}
}
