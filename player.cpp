#include "player.h"
#include "bullet.h"
#include <iostream>

Player::Player()
{
    Vector2 position;
    playerSprite = GifSprite(this, "assets/player.gif");
    position.x = GetScreenWidth() / 2 - playerSprite.getWidth() / 2;
    position.y = GetScreenHeight() - (playerSprite.getHeight() * 1.25);
    setPosition(position);
    speed = 10;
}

void Player::update(bool paused)
{
    handleInput(paused);
    playerSprite.update();
    renderBullets(paused);
}

Vector3 Player::getCollisionCircle() {
    Vector3 circle;
    circle.x = getPosition().x + playerSprite.getWidth()/2;
    circle.y = getPosition().y + playerSprite.getHeight()/2;;
    circle.z = float(playerSprite.getHeight())/2.0;
    return circle;
}

void Player::shoot()
{
    // Create a bullet.
    Bullet *bullet = new Bullet(this);
    Vector2 p = getPosition();
    p.x = p.x + playerSprite.getWidth()/2 - 64/2;
    bullet->setPosition(p);
    bullets.push_back(bullet);
}

std::vector<Bullet *> Player::getBullets() {
    return bullets;
}

void Player::deleteBullet(int index) {
    bullets.erase(bullets.begin()+index);
}

void Player::renderBullets(bool paused) {
    for (int i = 0; i < bullets.size(); i++) {
        if(bullets[i]->getPosition().y < 0) {
            bullets.erase(bullets.begin()+i);
            std::cout<<"Current bullets: "<<bullets.size()<<std::endl;
        } else {
            bullets[i]->update(paused);
        }
    }
}

void Player::handleInput(bool paused)
{
    if (!paused)
    {
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            Vector2 pos = getPosition();
            if (pos.x < GetScreenWidth() - playerSprite.getWidth())
            {
                pos.x = pos.x + speed;
                setPosition(pos);
            }
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            Vector2 pos = getPosition();
            if (pos.x > 0)
            {
                pos.x = pos.x - speed;
                setPosition(pos);
            }
        }
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            Vector2 pos = getPosition();
            if (pos.y > 0)
            {
                pos.y = pos.y - speed;
                setPosition(pos);
            }
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            Vector2 pos = getPosition();
            if (pos.y < GetScreenHeight() - playerSprite.getHeight())
            {
                pos.y = pos.y + speed;
                setPosition(pos);
            }
        }
        if(IsKeyPressed(KEY_SPACE)) {
            shoot();
        }
    }
}