#pragma once
#include "raylib.h"

class Enemy
{
public:
	Enemy(Vector2 enemySpawnPos);
	void Update(float deltaTime);
	void Draw() const;
	bool IsItBelow() const;
	bool IsVisible() const;
	Rectangle Get_Rect() const;
	void Hit();
	bool IsHit() const;

private:
	Vector2 enemyPosition;
	bool enemyHit = false;
};