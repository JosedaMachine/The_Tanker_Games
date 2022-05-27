// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

// when you are not using the methods of a calls, just
// say that it exists, that saves time when parsing files
class GameObject;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	std::vector<GameObject*> objs_;
};

