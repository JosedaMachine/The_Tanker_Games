#ifndef BULLET_H_
#define BULLET_H_

#include "../Utils/GameObject.h"
#include <vector>

class Bullet: public GameObject {
public:
    Bullet(Vector2D vel);
    virtual ~Bullet();
    void update() override;
private:
    Vector2D vel_;
	float speed_;

    bool hola;
};
#endif