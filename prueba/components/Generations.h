#ifndef GENERATIONS_H_
#define GENERATIONS_H_

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Generations : public Component {
public:
	Generations(int gen) : gen_(gen) {}

	virtual ~Generations() {}

	inline int& getLives() { return gen_; }

private:
	int gen_;
};
#endif