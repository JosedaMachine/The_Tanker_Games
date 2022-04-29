#include "RenderSystem.h"


#include "../components/AsteroidType.h"
#include "../components/Health.h"
#include "../components/FrameImage.h"
#include "../Systems/GameCtrlSystem.h"




RenderSystem::RenderSystem() : playerTexture(nullptr), player(nullptr) {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::init() {
	playerTexture = &sdlutils().images().at("fighter");
	bulletTexture = &sdlutils().images().at("bullet");
}

void RenderSystem::update() {
	GameCtrlSystem* gameSys = manager_->getSystem<GameCtrlSystem>();

	for (Entity* e : manager_->getEnteties()) {
		auto tr = manager_->getComponent<Transform>(e);
		player = manager_->getHandler<Player>();
		if (player != nullptr && player == e) {
			dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
			playerTexture->render(dest, tr->rotation_);
			auto* health_ = manager_->getComponent<Health>(e);

			//Render Lifes
			for (int i = 0; i < health_->lives; i++) {
				float x = health_->size_.getX();
				Vector2D pos = health_->pos_;
				SDL_Rect dest = build_sdlrect(pos, x, x);
				health_->tex->render(dest, 0.0f);
				health_->pos_.setX(health_->pos_.getX() + x);
			}
			health_->pos_.set(health_->iniPos_);

		}
		else if (manager_->hasGroup<Bullet_grp>(e)) {
			dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
			bulletTexture->render(dest, manager_->getComponent<Transform>(player)->rotation_);
		}
		else if (manager_->hasGroup<Asteroid_grp>(e)) {
			auto* type = manager_->getComponent<AsteroidType>(e);
			auto* framedImage = manager_->getComponent<FrameImage>(e);
			//If the time passed is equal to the frameRate, we advance the animation
			if (sdlutils().currRealTime() - framedImage->lastTime >= framedImage->timer) {
				framedImage->lastTime = (sdlutils().currRealTime());
				if (framedImage->posX != framedImage->wholeSize.getX() - 1) ++framedImage->posX;
				else {
					if (framedImage->posY != framedImage->wholeSize.getY() - 1) {
						++framedImage->posY;
						framedImage->posX = (int)framedImage->iniPos.getX();
					}
					else {
						framedImage->posX = (int)framedImage->iniPos.getX();
						framedImage->posY = (int)framedImage->iniPos.getY();
					}
				}
				framedImage->src_ = { framedImage->sizeXF * framedImage->posX,framedImage->sizeYF * framedImage->posY, framedImage->sizeXF, framedImage->sizeYF };
			}

			//Create the destination Rectangle
			SDL_Rect dest = build_sdlrect(tr->pos_, tr->width_, tr->height_);
			//Render the texture with the sourceRectangle
			framedImage->tex_->render(framedImage->src_, dest, tr->rotation_);
		}
	}

	Texture* mssg = gameSys->getMessageTexture();
	if (mssg != nullptr) mssg->render((sdlutils().width() - mssg->width()) / 2, sdlutils().height() / 2 - (mssg->height() / 2));
}
