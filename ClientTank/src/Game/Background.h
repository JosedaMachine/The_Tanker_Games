#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "../SDL_Utils/GameObject.h"
#include <vector>

class Background: public GameObject {
public:
    Background();
    virtual ~Background();
    void update() override;
private:
};
#endif