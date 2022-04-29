// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

#include <algorithm>

Manager::Manager() {
}

Manager::~Manager() {
	for (auto e : entities_) {
		delete e;
	}
}

void Manager::refresh() {

	// remove dead entities from the list of entities
	entities_.erase( //
			std::remove_if( //
					entities_.begin(), //
					entities_.end(), //
					[](const Entity *e) { //
						if (e->active_) {
							return false;
						} else {
							delete e;
							return true;
						}
					}), //
			entities_.end());
}
