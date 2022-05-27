#include "Tank.h"

Tank::Tank(int w, int h, SDL_Renderer* rend){
    heightApp_ =h;
    widthApp_ = w; 
    renderer_ =rend;
}

Tank::~Tank() {

}

void Tank::handleInput(const SDL_Event &e) {

	// if (e.type == SDL_KEYDOWN) {
	// 	if (e.key.keysym.scancode == up_) {
	// 		vel_.setY(-speed_);
	// 	} else if (e.key.keysym.scancode == down_) {
	// 		vel_.setY(speed_);
	// 	} else if (e.key.keysym.scancode == stop_) {
	// 		vel_.setY(0.0f);
	// 	}
	// }
}

void Tank::update() {
	// pos_ = pos_ + vel_;

	// if (pos_.getY() < 0) {
	// 	pos_.setY(0);
	// 	vel_.setY(0);
	// } else if (pos_.getY() + height_ > heightApp_) {
	// 	pos_.setY(heightApp_ - height_);
	// 	vel_.setY(0);
	// }

}