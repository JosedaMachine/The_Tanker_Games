// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>
#include <bitset>
#include <memory>

#include "Component.h"
#include "ecs.h"

class Manager;

struct Entity {

	friend Manager;

private:

	bool active_;
	std::array<std::unique_ptr<Component>, ecs::maxComponent> _cmps = { };
	std::bitset<ecs::maxGroup> groups_;
};
