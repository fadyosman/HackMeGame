#include "bullet.h"
#include <iostream>

Bullet::Bullet(Node *parent)
{
    sprite = GifSprite(this, "assets/fireball.gif");
    speed = 12;
}

void Bullet::update(bool paused)
{
    if (!paused)
    {
        Vector2 p = getPosition();
        p.y = p.y - speed;
        setPosition(p);
    }
    sprite.update();
}

Vector3 Bullet::getCollisionCircle() {
    Vector3 circle;
    circle.x = getPosition().x + sprite.getWidth()/2;
    circle.y = getPosition().y + sprite.getHeight()/2;;
    circle.z = float(sprite.getHeight())/2.5;
    return circle;
}