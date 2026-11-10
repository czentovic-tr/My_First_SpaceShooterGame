#pragma once
#include "Player.hpp"
#include "Enemy.hpp"
#include "constants.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"
#include <vector>

import std;

enum class GameState
{
	Playing,
	Win,
	Lost
};

class Game
{
public:
	Game();
	~Game();
	void Run();

private:
	Player player1;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	std::vector<Particle> particles;
	int score = 0;
	float enemySpawnTimer = 0.0f;
	int playerHP = playerMaxHP;
	float timePassed = 0.0f;
	GameState state = GameState::Playing;
	
	void Update(float deltaTime);
	void Draw() const;
	void Restart();
	void SpawnExplosion(Vector2 center);
};