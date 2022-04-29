#pragma once
#include "../ecs/Component.h"

struct AsteroidType : public Component
{
public:
	enum class Type { A, B };
	AsteroidType(Type type) : type_(type) {};


	~AsteroidType(){
	}


	Type type_;
};
