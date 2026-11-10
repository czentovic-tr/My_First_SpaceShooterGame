#include "Enemy.hpp"
#include "constants.hpp"


Enemy::Enemy(Vector2 enemySpawnPos)
{
	enemyPosition = enemySpawnPos;
}

void Enemy::Update(float deltaTime)
{
	enemyPosition.y += enemySpeed * deltaTime;
}

void Enemy::Draw() const
{
	DrawRectangleV(enemyPosition, Vector2{enemyWidth, enemyHeight}, RED);

}

bool Enemy::IsItBelow() const
{
	if (enemyPosition.y > windowHeight)
	{
		return true;
	}
	return false;
}

bool Enemy::IsVisible() const
{
	if (enemyPosition.y + enemyHeight <= 0.0f)
	{
		return false;
	}
	if (enemyPosition.y >= windowHeight)
	{
		return false;
	}
	return true;
}

Rectangle Enemy::Get_Rect() const
{
	return Rectangle{ enemyPosition.x, enemyPosition.y, enemyWidth, enemyHeight };
}

void Enemy::Hit()
{
	enemyHit = true;
}

bool Enemy::IsHit() const
{
	return enemyHit;
}