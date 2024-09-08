#include "sprite.h"
#include <iostream>

GifSprite::GifSprite()
{

}

GifSprite::GifSprite(Node *n, char *imagePath)
{
    image = LoadImageAnim(imagePath, &animFrames);
    texture = LoadTextureFromImage(image);
    delayCounter = 0;
    delay = 4;
    currentFrame = 0;
    node = n;
}

void GifSprite::update() {
    delayCounter++;
    if (delayCounter >= delay) {
        currentFrame++;
        if(currentFrame >= animFrames) currentFrame = 0;
        
        int nextFrameDataOffset = image.width*image.height*4*currentFrame;

        UpdateTexture(texture, (unsigned char *)image.data + nextFrameDataOffset);

        delayCounter = 0;
    }
    //std::cout<<node->getPosition().x<<","<<node->getPosition().y<<"\n";
    DrawTexture(texture, node->getPosition().x, node->getPosition().y, WHITE);
}

int GifSprite::getHeight() {
    return image.height;
}

int GifSprite::getWidth() {
    return image.width;
}

GifSprite::~GifSprite()
{

}