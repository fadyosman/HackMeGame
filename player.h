#ifndef PLAYER_H
#define PLAYER_H

#include "core/node.h"
#include "core/sprite.h"
#include "bullet.h"
#include <vector>

class Player : public Node {
    public:
        Player();
        void update(bool paused);
        Vector3 getCollisionCircle();
        std::vector<Bullet *> getBullets();
        void deleteBullet(int index);
    private:
        void handleInput(bool paused);
        void shoot();
        void renderBullets(bool paused);
        GifSprite playerSprite;
        int speed;
        std::vector<Bullet *> bullets;
};

#endif