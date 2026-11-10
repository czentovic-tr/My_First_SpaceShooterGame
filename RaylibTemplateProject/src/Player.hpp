#pragma once
#include "raylib.h"

class Player
{
public:
	Player();
	void Update(float deltaTime);
	void Draw() const;
	Vector2 TopPoint() const;
	Vector2 LeftPoint() const;
	Vector2 RightPoint() const;
	bool IsTouching(Rectangle enemyRect) const;
private:
	Vector2 playerPosition;
};