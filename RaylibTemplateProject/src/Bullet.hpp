#pragma once
#include "raylib.h"

class Bullet
{
public:
	Bullet(Vector2 bulletSpawnPos);
	void Update(float deltaTime);
	void Draw() const;
	bool IsItAbove() const;
	Rectangle Get_Rect() const;
	void Hit();
	bool IsHit() const;

private:
	Vector2 bulletPosition;
	bool bulletHit = false;
};