#include "TankClient.h"

#include "../SDL_Utils/GameObject.h"
#include "../SDL_Utils/macros.h"
#include "../SDL_Utils/Environment.h"

#include "../Game/Font.h"
#include "../Game/Tank.h"
#include "../Game/Bullet.h"
#include "../Game/Obstacle.h"
#include "../Game/Background.h"

#include "../Managers/GameManager.h"

TankClient::TankClient(const char *s, const char *p) : client_socket(s, p), player_1(nullptr), player_2(nullptr), bullet_1(nullptr), bullet_2(nullptr),
								tank_1_won(false), currentState(TankMessageServer::ServerState::WAITING), nextState(TankMessageServer::ServerState::EMPTY){};

TankClient::~TankClient() {}

void TankClient::init(int w, int h)
{
	Environment::init("The Tanker's Games", w, h);
	GameManager::init();

	InitData data;
	data.dim = Vector2D(TANK_SIZE, TANK_SIZE);
	data.rot = 0;

	changeState(currentState);

	// init connection
	std::thread([this]()
				{ client_message_thread(); })
		.detach();

	sendMatchMessage(TankMessageClient::ClientMessageType::REGISTER, &data);
	std::cout << "Trying to log...\n";
}

void TankClient::run()
{
	SDL_Event event;

	while (nextState != TankMessageServer::ServerState::SERVER_QUIT)
	{
		checkState();

		Uint32 startTime = environment().currRealTime();
		while (SDL_PollEvent(&event))
		{
			//Salir del server
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
				currentState = TankMessageServer::ServerState::SERVER_QUIT;
				continue;
			}

			if ((event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN)) {
				std::cout << "Lets Begin\n";
				sendGameMessage(TankMessageClient::InputType::PLAY);
				continue;
			}

			for (auto &o : objs_)
				if (o->isEnabled())
					o->handleInput(event);
		}

		if (currentState == TankMessageServer::ServerState::SERVER_QUIT)
			break;

		// update
		for (auto &o : objs_)
			if (o->isEnabled())
				o->update();

		refresh();

		environment().clearRenderer({0, 0, 0});

		// render
		for (auto &o : objs_)
			if (o->isEnabled())
				o->render();

		environment().presentRenderer();

		Uint32 frameTime = environment().currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	sendMatchMessage(TankMessageClient::ClientMessageType::QUIT);
	std::cout << "Quitting...\n";
}

void TankClient::shutdown()
{
	clearGameObjects();
}

void TankClient::client_message_thread()
{
	TankMessageServer server_recv_msg;
	Socket *net_socket = new Socket(client_socket);
	while (true)
	{
		client_socket.recv(server_recv_msg, net_socket);
		switch (server_recv_msg.type)
		{
		case TankMessageServer::ServerMessageType::UPDATE_STATE:
			nextState = server_recv_msg.state;
			if(nextState == TankMessageServer::ServerState::GAME_OVER)
				tank_1_won = server_recv_msg.playerOneHasWon;
			break;
		case TankMessageServer::ServerMessageType::UPDATE_INFO:
			updateGOsInfo(&server_recv_msg);
			break;
		case TankMessageServer::ServerMessageType::ACTION:
		{
			switch (server_recv_msg.action_)
			{
			case TankMessageServer::ActionType::CREATE_BULLET_1:
			{
				if (bullet_1 == nullptr)
					// pos_bullet_1 in this context is used as an auxiliar for the creation of each bullet
					shoot(bullet_1, server_recv_msg.pos_bullet_1, server_recv_msg.dim_bullet);
					// std::cout << "Bullet created1: " << bullet_1 << "\n";
				break;
			}
			case TankMessageServer::ActionType::CREATE_BULLET_2: 
				if (bullet_2 == nullptr)
					// pos_bullet_1 in this context is used as an auxiliar for the creation of each bullet
					shoot(bullet_2, server_recv_msg.pos_bullet_1, server_recv_msg.dim_bullet);
					// std::cout << "Bullet created2: " << bullet_2 << "\n";
				break;
			case TankMessageServer::ActionType::DESTROY_BULLET_1: 
				removeBullet(bullet_1);
				break;
			case TankMessageServer::ActionType::DESTROY_BULLET_2: 
				removeBullet(bullet_2);
				break;
			case TankMessageServer::ActionType::DAMAGE_1:
				removeBullet(bullet_2);
				std::cout << "Vida 1:" << server_recv_msg.life << "\n";
				player_1->setLife(server_recv_msg.life);
				break;
			case TankMessageServer::ActionType::DAMAGE_2: 
				removeBullet(bullet_1);
				std::cout << "Vida 2:" << server_recv_msg.life << "\n";
				player_2->setLife(server_recv_msg.life);
				break;
			case TankMessageServer::ActionType::CREATE_OBSTACLE: 
				Obstacle* o = new Obstacle();
				o->setTransform(server_recv_msg.pos_bullet_1);
				o->setDimensions(server_recv_msg.dim_bullet.getX(), server_recv_msg.dim_bullet.getY());
				o->setTexture("./resources/images/obstacle.png");
				gObjsToAdd_.push_back(o);
				break;
			}
			break;
		}
		}
	}
}

void TankClient::updateGOsInfo(TankMessageServer *msg)
{
	if(currentState == TankMessageServer::ServerState::PLAYING) {
		// //playerOne
		player_1->setTransform(msg->pos_t1);
		player_1->setRotation(msg->rot_t1);
		// //playerTwo
		player_2->setTransform(msg->pos_t2);
		player_2->setRotation(msg->rot_t2);

		if (bullet_1)
			bullet_1->setTransform(msg->pos_bullet_1);

		if (bullet_2)
			bullet_2->setTransform(msg->pos_bullet_2);
	}
}

void TankClient::shoot(Bullet *&bullet, const Vector2D &pos, const Vector2D &dim) {
	bullet = new Bullet();
	bullet->setTransform(pos.getX(), pos.getY());
	bullet->setDimensions(dim.getX(), dim.getY());
	bullet->setTexture("./resources/images/bullet.png");

	objs_.push_back(bullet);
}

void TankClient::removeBullet(Bullet *&bullet) {
	if (bullet != nullptr) {
		bullet->setEnabled(false);
		bullet = nullptr;
	}
}

void TankClient::checkState()
{
	if (nextState != TankMessageServer::ServerState::EMPTY && currentState != nextState)
	{
		changeState(nextState); // this makes it so there's no problems with thread

		currentState = nextState;
		nextState = TankMessageServer::ServerState::EMPTY;

		printf("Curr St: %d -- Next St: %d \n", (int)currentState, (int)nextState);
	}
}

void TankClient::changeState(const TankMessageServer::ServerState state)
{
	clearGameObjects();

	switch (state)
	{
	case TankMessageServer::ServerState::WAITING:{
		int x = 780;
		loadScreen("./resources/images/init.png", "./resources/fonts/NES-Chimera.ttf", "Waiting for another player to connect...",
				   Vector2D(640 - (x/2), 600), Vector2D(x, 50), {0, 0, 0}, 20);
		break;
	}
	case TankMessageServer::ServerState::READY:{
		int x = 670;
		loadScreen("./resources/images/init.png", "./resources/fonts/NES-Chimera.ttf", "Ready to play, press ENTER",
				   Vector2D(640 - (x/2) - 10, 600), Vector2D(x, 50), {208, 72, 72}, 20);
		break;
	}
	case TankMessageServer::ServerState::PLAYING:
		std::cout << "Juega";
		playLoad();
		break;
	case TankMessageServer::ServerState::GAME_OVER:{
		int x = 700;
		std::string pl = tank_1_won == true ? "1" : "2";
		SDL_Color color;
		if(tank_1_won) color = {67, 226, 114};
		else color = {226, 83, 67};
		
		loadScreen("./resources/images/init.png", "./resources/fonts/NES-Chimera.ttf", "Player " + pl + " Win!",
				Vector2D(640 - (x/2), 600), Vector2D(x, 50), color, 20);
		break;
	}
	default:
		break;
	}
}

void TankClient::loadScreen(const std::string &textFile, const std::string &fontFile, const std::string &text,
							  const Vector2D &textPos, const Vector2D &textDim, const SDL_Color &color, const int &size)
{
	Background *bG = new Background();
	bG->setTransform(0, 0);
	bG->setDimensions(environment().width(), environment().height());
	bG->setTexture(textFile);

	objs_.push_back(bG);

	Font *f = new Font(fontFile, text, color, size);
	f->setTransform(textPos.getX(), textPos.getY());
	f->setDimensions(textDim.getX(), textDim.getY());

	objs_.push_back(f);
}

void TankClient::playLoad()
{
	Background *bG = new Background();
	bG->setTransform(0, 0);
	bG->setDimensions(environment().width(), environment().height());
	bG->setTexture("./resources/images/background.png");

	objs_.push_back(bG);

	for(int i = 0; i < gObjsToAdd_.size(); i++)
		objs_.push_back(gObjsToAdd_[i]);
	gObjsToAdd_.clear();

	float speed = 2.0f;
	float initialLives = 3;
	player_1 = new Tank(this, initialLives, 30);
	player_1->setTransform(200, environment().height() / 2);
	player_1->setDimensions(TANK_SIZE, TANK_SIZE);
	player_1->setTexture("./resources/images/tank_blue.png");
	player_1->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player_1->setSpeed(speed);

	objs_.push_back(player_1);

	player_2 = new Tank(this, initialLives, environment().width() - 3*50 - 21);
	player_2->setTransform(800, environment().height() / 2);
	player_2->setDimensions(TANK_SIZE, TANK_SIZE);
	player_2->setTexture("./resources/images/tank_red.png");
	player_2->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player_2->setSpeed(speed);

	objs_.push_back(player_2);
}

void TankClient::sendGameMessage(TankMessageClient::InputType input)
{
	TankMessageClient login;
	login.type = TankMessageClient::ClientMessageType::HANDLE_INPUT;
	login.input = input;
	client_socket.send(login, client_socket);
}

void TankClient::sendMatchMessage(TankMessageClient::ClientMessageType msg, InitData *data)
{	
	TankMessageClient login;
	login.type = msg;

	if (data != nullptr)
		login.setDefaultValues(GameManager::instance()->getRelativeScenerioLimits().getX(), //Left
							  GameManager::instance()->getScenerioLimits().getX(), //Right
							  GameManager::instance()->getRelativeScenerioLimits().getY(),//Top 
							  GameManager::instance()->getScenerioLimits().getY() + 45, //Bottom
							  data->dim, data->rot);

	client_socket.send(login, client_socket);
	printf("Sending Match Message...\n");
}

void TankClient::refresh()
{
	objs_.erase(std::remove_if(objs_.begin(), objs_.end(),
							   [](const GameObject *e)
							   {
								   if (e->isEnabled())
									   return false;
								   else
								   {
									   delete e;
									   return true;
								   }
							   }),
				objs_.end());
}

void TankClient::clearGameObjects()
{
	for (unsigned int i = 0; i < objs_.size(); i++){
		printf("Destroyed");
		if(objs_[i] != nullptr)
			delete objs_[i];
		objs_[i] = nullptr;
	}
	objs_.clear();
}