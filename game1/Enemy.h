#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class ENEMY {
public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;

    ENEMY() : dx(0), dy(0), currentFrame(0), life(false) {} // Инициализация переменных

    void set(Texture& image, int x, int y);
    void update(float time);
    void Collision();
};

#endif
