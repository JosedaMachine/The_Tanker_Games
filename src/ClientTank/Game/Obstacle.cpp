#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle() : GameObject() {
}

Obstacle::~Obstacle() {
        std::cout << "Borrada\n";
}