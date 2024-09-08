#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include "node.h"
class GifSprite
{
private:
    Image image;
    Texture2D texture;
    int animFrames;
    int currentFrame;
    //Controls the speed of the animation.
    int delay;
    int delayCounter;
    Node *node;

public:
    GifSprite();
    GifSprite(Node* parent, char *imagePath);
    void update();
    int getWidth();
    int getHeight();
    ~GifSprite();
};

#endif