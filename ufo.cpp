#include "ufo.h"
#include <iostream>

UFO::UFO(Node *parent)
{
    sprite = GifSprite(this, "assets/ufo.gif");
    speed = 12;
}

void UFO::update(bool paused)
{
    if (!paused)
    {
        Vector2 p = getPosition();
        p.y = p.y + speed;
        setPosition(p);
    }
    sprite.update();
    // Vector3 circle = getCollisionCircle();
    // DrawCircle(circle.x, circle.y, circle.z, BLUE);
}

Vector3 UFO::getCollisionCircle() {
    Vector3 circle;
    circle.x = getPosition().x + sprite.getWidth()/2;
    circle.y = getPosition().y + sprite.getHeight()/2;;
    circle.z = float(sprite.getHeight())/2;
    return circle;
}