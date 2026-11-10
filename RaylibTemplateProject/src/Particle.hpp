#pragma once
#include "raylib.h"

class Particle
{
public:
	Particle(Vector2 startPos, Vector2 speed);
	void Update(float deltaTime);
	void Draw() const;
	bool IsVisible() const;
	bool IsDead() const;

private:
	Vector2 particlePosition;
	Vector2 particleSpeed;
	float timeReamined;
};