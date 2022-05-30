#include "App.h"


#include "../Game/Background.h"
#include "../Game/Tank.h"
#include "../Net/Socket.h"
#include "../SDL_Utils/GameObject.h"
#include "../SDL_Utils/macros.h"
#include "../SDL_Utils/Environment.h"

#include "GameManager.h"

App::App(const char *s, const char *p) : client_socket(s, p){
};

App::~App() {}

void App::init(int w, int h) {
	Environment::init("The Tanker's Games", w, h);
	GameManager::init();

	Background* bG = new Background();
	bG->setTransform(0, 0);
	bG->setDimensions(w, h);
	bG->setTexture("./resources/images/background.png");

	objs_.push_back(bG);

	float speed = 2.0f;
	player_1 = new Tank(&objs_);
	player_1->setTransform(GameManager().getScenerioLimits().getX() * 0.2, environment().height() / 2);
	player_1->setDimensions(60, 60);
	player_1->setTexture("./resources/images/tank_blue.png");
	player_1->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player_1->setSpeed(speed);
	objs_.push_back(player_1);

	player_2 = new Tank(&objs_);
	player_2->setTransform(GameManager().getScenerioLimits().getX() * 0.8, environment().height() / 2);
	player_2->setDimensions(60, 60);
	player_2->setTexture("./resources/images/tank_red.png");
	player_2->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player_2->setSpeed(speed);

	objs_.push_back(player_2);

	sendMatchMessage(TankMessageClient::ClientMessageType::REGISTER);
	std::cout << "Trying to log...\n";
}

void App::run()
{
	bool close = false;
	SDL_Event event;

	// animation loop
	while (!close)
	{
		Uint32 startTime = environment().currRealTime();

		// handle input
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				close = true;
				continue;
			}

			for (auto &o : objs_){
				if(o->isEnabled())
					o->handleInput(event);
			}
		}

		// update
		for (auto &o : objs_){
			if(o->isEnabled())
				o->update();
		}

		refresh();

		environment().clearRenderer();

		// render
		for (auto &o : objs_){
			if(o->isEnabled())
				o->render();
		}

		environment().presentRenderer();
		Uint32 frameTime = environment().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	sendMatchMessage(TankMessageClient::ClientMessageType::QUIT);
	std::cout << "Quitting...\n";
}

void App::sendMatchMessage(TankMessageClient::ClientMessageType msg){
	TankMessageClient login;
	login.type = msg;
	client_socket.send(login, client_socket);
}

void App::shutdown()
{
	for (unsigned int i = 0; i < objs_.size(); i++)
		delete objs_[i];
}

void App::refresh(){
	objs_.erase( //
		std::remove_if( //
			objs_.begin(), //
			objs_.end(), //
			[](const GameObject* e) { //
				if (e->isEnabled()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
			}), //
		objs_.end());
}