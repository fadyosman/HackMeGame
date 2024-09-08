#ifndef BULLET_H
#define BULLET_H

#include "core/node.h"
#include "core/sprite.h"

class Bullet : public Node {
    private:
        int speed;
        GifSprite sprite;
    public:
        Bullet(Node *parent);
        void update(bool paused);
        Vector3 getCollisionCircle();
};

#endif