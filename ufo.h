#ifndef UFO_H
#define UFO_H

#include "core/node.h"
#include "core/sprite.h"

class UFO : public Node {
    private:
        int speed;
        GifSprite sprite;
    public:
        UFO(Node *parent);
        void update(bool paused);
        Vector3 getCollisionCircle();
};

#endif