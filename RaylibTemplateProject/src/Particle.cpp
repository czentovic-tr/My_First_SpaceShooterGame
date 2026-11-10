#include "Particle.hpp"
#include "constants.hpp"

Particle::Particle(Vector2 startPos, Vector2 speed)
{
	particlePosition = startPos;
	particleSpeed = speed;
	timeReamined = particleLifeTime;
}

void Particle::Update(float deltaTime)
{
	particlePosition.x += particleSpeed.x * deltaTime;
	particlePosition.y += particleSpeed.y * deltaTime;
	timeReamined -= deltaTime;
}

//Added Fading
void Particle::Draw() const
{
	DrawCircleV(particlePosition, particleSize, Fade(RED, timeReamined / particleLifeTime));
}

bool Particle::IsDead() const
{
	if (timeReamined <= 0.0f)
	{
		return true;
	}
	return false;
}

bool Particle::IsVisible() const
{
	const Rectangle rec{ 0.0f,0.0f,windowWidth,windowHeight };
	return CheckCollisionPointRec(particlePosition, rec);
}