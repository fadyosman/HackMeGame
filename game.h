#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include "ufo.h"
#include "bullet.h"
#include "player.h"

class Game
{
private:
    Color clearColor;
    std::vector<UFO *> ufos;
    int score;
    int health;
    Player *player;
public:
    Game(int w, int h, char *title, int fps);
    // Main game loop.
    void createUFO();
    void renderUFOs(bool paused);
    void run();
    void checkUFOBulletCollision(std::vector<Bullet *> bullets);
    void checkPlayerUFOCollision();
    void restartGame();
    ~Game();
};

#endif