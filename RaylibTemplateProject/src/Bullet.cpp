#include "Bullet.hpp"
#include "constants.hpp"

Bullet::Bullet(Vector2 bulletSpawnPos)
{
	bulletPosition = bulletSpawnPos;
}

void Bullet::Update(float deltaTime)
{
	bulletPosition.y -= bulletSpeed * deltaTime;
}

void Bullet::Draw() const
{
	DrawRectangleV(bulletPosition, Vector2{ bulletWidth, bulletHeight }, YELLOW);
}

bool Bullet::IsItAbove() const
{
	if (bulletPosition.y + bulletHeight < 0.0f)
	{
		return true;
	}
	return false;
}

Rectangle Bullet::Get_Rect() const
{
	return Rectangle{ bulletPosition.x, bulletPosition.y, bulletWidth, bulletHeight };
}

void Bullet::Hit()
{
	bulletHit = true;
}

bool Bullet::IsHit() const
{
	return bulletHit;
}