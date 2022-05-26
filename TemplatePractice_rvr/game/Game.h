#ifndef GAME_H_
#define GAME_H_

#include <memory>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class Entity;
class GameManager;

class Game {
public:

	Game();
	virtual ~Game();
	void init();
	void start();

private:

	std::unique_ptr<Manager> mngr_;
};
#endif 