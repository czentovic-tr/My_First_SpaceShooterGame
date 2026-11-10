#include "Game.hpp"
#include "constants.hpp"
#include "raylib.h"



Game::Game()
{
	InitWindow(windowWidth, windowHeight, "Jam 3");
}

Game::~Game()
{
	CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        Update(deltaTime);
        Draw();
    }
}

//part of experiment - check if enemy got hit or went out of map
bool isEnemyGone(Enemy enemy)
{
    if (enemy.IsItBelow())
    {
        return true;
    }
    if (enemy.IsHit())
    {
        return true;
    }
    return false;
}

//part of experiment - check if bullet got hit or went out of map
bool isBulletGone(Bullet bullet)
{
    if (bullet.IsItAbove())
    {
        return true;
    }
    if (bullet.IsHit())
    {
        return true;
    }
    return false;
}

//check the explosion state
bool isParticleFaded(Particle particle)
{
    return particle.IsDead();
}

//random particle spawn
void Game::SpawnExplosion(Vector2 center)
{
    for (int i = 0; i < particleCount; i++)
    {
        const float speedX = static_cast<float>(GetRandomValue(-particleSpeed, +particleSpeed));
        const float speedY = static_cast<float>(GetRandomValue(-particleSpeed, +particleSpeed));
        particles.push_back(Particle(center, Vector2{ speedX,speedY }));
    }
}

//Game update here
void Game::Update(float deltaTime)
{
    //Pause the game fully
    if (state != GameState::Playing)
    {
        if (IsKeyPressed(KEY_R))
        {
            Restart();
        }
        return;
    }

    player1.Update(deltaTime);

    //shooting
    if (IsKeyPressed(KEY_SPACE))
    {
        const float bulletX = player1.TopPoint().x - bulletWidth / 2.0f;
        const float bulletY = player1.TopPoint().y - bulletHeight;
        bullets.push_back(Bullet(Vector2{ bulletX, bulletY }));
    }


    timePassed += deltaTime;
    enemySpawnTimer += deltaTime;

    if (enemySpawnTimer >= enemyInterval)
    {
        enemySpawnTimer -= enemyInterval;

        //enemy spawn point for random X direction
        const int maxXpos = static_cast<int>(windowWidth - enemyWidth);
        const int randomXpos = GetRandomValue(0, maxXpos);
        const float enemyXspawn = static_cast<float>(randomXpos);
        enemies.push_back(Enemy(Vector2{ enemyXspawn, -enemyHeight }));
    }

    //enemy update
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update(deltaTime);
    }

    //collision between player and enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        if (player1.IsTouching(enemies[i].Get_Rect()))
        {
            enemies[i].Hit();
            playerHP -= 1;
        }
    }

    //bullet update
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update(deltaTime);
    }

    //bullet collade with enemy
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int b = 0; b < enemies.size(); b++)
        {
            if (CheckCollisionRecs(bullets[i].Get_Rect(), enemies[b].Get_Rect()))
            {
                bullets[i].Hit();
                enemies[b].Hit();

                //get center of the enemy and start explosion if got hit
                //const Rectangle enemyRect = enemies[b].Get_Rect();
                //const float centerX = enemyRect.x + enemyRect.width / 2.0f;
                //const float centerY = enemyRect.y + enemyRect.height / 2.0f;
                SpawnExplosion(Vector2{ enemies[b].Get_Rect().x + enemies[b].Get_Rect().width / 2.0f, enemies[b].Get_Rect().y + enemies[b].Get_Rect().height / 2.0f });
                score += 1;
            }
        }
    }

    //remove bullets 
    std::erase_if(bullets, isBulletGone);

    for (int i = 0; i < particles.size();i++)
    {
        particles[i].Update(deltaTime);
    }

    //remove particles
    std::erase_if(particles, isParticleFaded);

    //remove enemies
    std::erase_if(enemies, isEnemyGone);

    //win-loss condition
    if (playerHP <= 0)
    {
        state = GameState::Lost;
    }
    else if (timePassed >= winningTime)
    {
        state = GameState::Win;
    }
}

void Game::Restart()
{
    player1 = Player();
    enemies.clear();
    enemySpawnTimer = 0.0f;
    playerHP = playerMaxHP;
    timePassed = 0.0f;
    state = GameState::Playing;
    bullets.clear();
    particles.clear();
    score = 0;
}

void Game::Draw() const
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    player1.Draw();
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].IsVisible())
        {
            enemies[i].Draw();
        }
    }
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }
    for (int i = 0;i < particles.size();i++) 
    {
        if (particles[i].IsVisible())
        {
            particles[i].Draw();
        }
    }
    DrawText(TextFormat("dt: %f", GetFrameTime()), 10, 10, 20, BLACK);
    DrawText(TextFormat("Enemy Count: %d", static_cast<int>(enemies.size())), 10, 50, 20, BLACK);
    DrawText(TextFormat("Lives: %d", playerHP), 10, 70, 20, BLACK);
    DrawFPS(10, 30);
    DrawText(TextFormat("Time: %.1f / %.0f", timePassed, winningTime), 10, 90, 20, BLACK);
    DrawText(TextFormat("Score: %d", score), 10, 110, 20, BLACK);

    if (state == GameState::Lost)
    {
        DrawText("YOU LOSE!", windowWidth / 2 - MeasureText("YOU LOSE!", 60) / 2, windowHeight / 2 - 30, 60, RED);
        DrawText("Press R to restart", windowWidth / 2 - MeasureText("Press R to restart", 20) / 2, windowHeight / 2 + 40, 20, RED);
    }
    if (state == GameState::Win)
    {
        DrawText("YOU WIN!", windowWidth / 2 - MeasureText("YOU WIN!", 60) / 2, windowHeight / 2 - 30, 60, RED);
        DrawText("Press R to restart", windowWidth / 2 - MeasureText("Press R to restart", 20) / 2, windowHeight / 2 + 40, 20, RED);
    }
    EndDrawing();
}