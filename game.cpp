#include "game.h"
#include "core/sprite.h"
#include "player.h"
#include "ufo.h"
#include <iostream>
#include <random>

Game::Game(int w, int h, char *title, int fps)
{
    InitWindow(w, h, title);
    // Otherwise escape will exit the window.
    SetExitKey(0);
    SetTargetFPS(fps);
    clearColor = RAYWHITE;
    player = new Player();
    // Initalize.
    score = 0;
    health = 10;
}

void Game::createUFO()
{
    // Create a bullet.
    UFO *ufo = new UFO(nullptr);
    Vector2 p;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> posx(0, GetScreenWidth());
    p.x = posx(rng);
    p.y = -20;
    ufo->setPosition(p);
    ufos.push_back(ufo);
}

void Game::renderUFOs(bool paused)
{
    for (int i = 0; i < ufos.size(); i++)
    {
        if (ufos[i]->getPosition().y > GetScreenHeight())
        {
            // ufos[i]->update(paused);
            ufos.erase(ufos.begin() + i);
            // std::cout<<"Current ufos: "<<ufos.size()<<std::endl;
        }
        else
        {
            ufos[i]->update(paused);
        }
    }
}

void Game::checkUFOBulletCollision(std::vector<Bullet *> bullets)
{
    bool col = false;
    for (int i = 0; i < ufos.size(); i++)
    {
        for (int j = 0; j < bullets.size(); j++)
        {
            Vector2 ufoCenter;
            Vector3 ccUFO = ufos[i]->getCollisionCircle();
            ufoCenter.x = ccUFO.x;
            ufoCenter.y = ccUFO.y;
            float ufoRadius = ccUFO.z;
            Vector2 bulletCenter;
            Vector3 ccBullet = bullets[j]->getCollisionCircle();
            bulletCenter.x = ccBullet.x;
            bulletCenter.y = ccBullet.y;
            float bulletRadius = ccBullet.z;
            col = CheckCollisionCircles(ufoCenter, ufoRadius, bulletCenter, bulletRadius);

            // DrawCircle(ufoCenter.x, ufoCenter.y, ufoRadius, BLUE);
            if (col)
            {
                ufos.erase(ufos.begin() + i);
                score += 10;
                player->deleteBullet(j);
                // No need to check the rest of the bullets.
                continue;
            }
        }
    }
}

void Game::checkPlayerUFOCollision()
{
    for (int i = 0; i < ufos.size(); i++)
    {
        Vector2 ufoCenter;
        Vector3 ccUFO = ufos[i]->getCollisionCircle();
        ufoCenter.x = ccUFO.x;
        ufoCenter.y = ccUFO.y;
        float ufoRadius = ccUFO.z;
        Vector2 playerCenter;
        Vector3 playerCC = player->getCollisionCircle();
        playerCenter.x = playerCC.x;
        playerCenter.y = playerCC.y;
        float playerRadius = playerCC.z;

        bool col = CheckCollisionCircles(ufoCenter, ufoRadius, playerCenter, playerRadius);
        if (col)
        {
            health -= 1;
            std::cout << "=====================Player hit==========================";
            ufos.erase(ufos.begin() + i);
        }
    }
}

void Game::restartGame()
{
    health = 10;
    score = 0;
    delete player;
    player = new Player();
    ufos.clear();
}

void Game::run()
{
    bool paused = false;
    int frame = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (health <= 0)
        {
            Vector2 dimentions = MeasureTextEx(GetFontDefault(), "Game Over", 50, 1);
            DrawText("Game Over", 512 - dimentions.x / 2, 512 - dimentions.y / 2, 50, RED);
            Vector2 dimentions2 = MeasureTextEx(GetFontDefault(), "Press 'Q' to exit, Press 'R' to restart the game.", 20, 1);
            DrawText("Press 'Q' to exit, Press 'R' to restart the game.", 512 - dimentions2.x / 2, 512 + dimentions2.y + dimentions.y / 2, 20, GRAY);
            if (IsKeyDown(KEY_Q))
                exit(0);
            if (IsKeyDown(KEY_R))
                restartGame();
            EndDrawing();
            continue;
        }

        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
        {
            paused = !paused;
        }

        if (IsKeyDown(KEY_R) && paused)
        {
            restartGame();
            paused = false;
        }

        if (IsKeyDown(KEY_Q) && paused)
            exit(0);

        if (frame % 10 == 0 && !paused)
        {
            createUFO();
        }
        frame++;

        ClearBackground(clearColor);
        player->update(paused);
        if (paused)
        {
            Vector2 dimentions = MeasureTextEx(GetFontDefault(), "PAUSED", 50, 1);
            DrawText("PAUSED", 512 - dimentions.x / 2, 512 - dimentions.y / 2, 50, GRAY);
            Vector2 dimentions2 = MeasureTextEx(GetFontDefault(), "Press 'Q' to exit, Press 'R' to restart the game.", 20, 1);
            DrawText("Press 'Q' to exit, Press 'R' to restart the game.", 512 - dimentions2.x / 2, 512 + dimentions2.y + dimentions.y / 2, 20, GRAY);
            Vector2 dimentions3 = MeasureTextEx(GetFontDefault(), "Press 'P' to unpause.", 20, 1);
            DrawText("Press 'P' to unpause.", 512 - dimentions3.x / 2, 512 + dimentions2.y + dimentions.y + dimentions2.y / 2, 20, GRAY);
        }

        player->getPosition();

        renderUFOs(paused);
        checkUFOBulletCollision(player->getBullets());
        checkPlayerUFOCollision();

        Color healthColor = GREEN;
        if (health < 8 && health > 5)
        {
            healthColor = ORANGE;
        }
        else if (health <= 5)
        {
            healthColor = RED;
        }
        DrawText(TextFormat("Score: %02i", score), 50, 60, 20, GRAY);
        DrawText(TextFormat("Health: %02i", health), 50, 90, 20, healthColor);

        EndDrawing();
    }
}

Game::~Game()
{
}