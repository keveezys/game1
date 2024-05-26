#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class PLAYER {
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    PLAYER(Texture& image);
    void update(float time);
    void Collision(int num);
};

#endif
