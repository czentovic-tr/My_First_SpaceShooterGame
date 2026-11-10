#include "Player.hpp"
#include "constants.hpp"
import std;

Player::Player()
{
	playerPosition.x = windowWidth / 2.0f;
	playerPosition.y = windowHeight - playerHeight * 2.0f;
}

void Player::Update(float deltaTime)
{
	//Starts with no movement, moves by key pressed
	Vector2 playerMovement{ 0.0f,0.0f };
	if (IsKeyDown(KEY_LEFT))
	{
		playerMovement.x -= 1.0f;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		playerMovement.x += 1.0f;
	}
	if (IsKeyDown(KEY_UP))
	{
		playerMovement.y -= 1.0f;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		playerMovement.y += 1.0f;
	}

	playerPosition.x += playerMovement.x * playerSpeed * deltaTime;
	playerPosition.y += playerMovement.y * playerSpeed * deltaTime;

	playerPosition.x = std::clamp(playerPosition.x, 0.0f, windowWidth - playerWith);
	playerPosition.y = std::clamp(playerPosition.y, 0.0f, windowHeight - playerHeight);
}

void Player::Draw() const
{
	DrawTriangle(TopPoint(), LeftPoint(), RightPoint(), BLUE);

}

Vector2 Player::TopPoint() const
{
	return Vector2{ playerPosition.x + playerWith / 2.0f, playerPosition.y };
}

Vector2 Player::LeftPoint() const
{
	return Vector2{ playerPosition.x, playerPosition.y + playerHeight };
}

Vector2 Player::RightPoint() const
{
	return Vector2{ playerPosition.x + playerWith, playerPosition.y + playerHeight };
}

bool Player::IsTouching(Rectangle enemyRect) const
{
	//get enemies 4 corner points
	const Vector2 topLeft{ enemyRect.x, enemyRect.y };
	const Vector2 topRight{ enemyRect.x + enemyRect.width, enemyRect.y };
	const Vector2 bottomLeft{ enemyRect.x, enemyRect.y + enemyRect.height };
	const Vector2 bottomRight{ enemyRect.x + enemyRect.width, enemyRect.y + enemyRect.height };

	//any corner points inside the player triangle?
	if (CheckCollisionPointTriangle(topLeft, TopPoint(), LeftPoint(), RightPoint()))
	{
		return true;
	}
	if (CheckCollisionPointTriangle(topRight, TopPoint(), LeftPoint(), RightPoint()))
	{
		return true;
	}
	if (CheckCollisionPointTriangle(bottomLeft, TopPoint(), LeftPoint(), RightPoint()))
	{
		return true;
	}
	if (CheckCollisionPointTriangle(bottomRight, TopPoint(), LeftPoint(), RightPoint()))
	{
		return true;
	}

	//any triangle points of the player inside the enemies?
	if (CheckCollisionPointRec(TopPoint(), enemyRect))
	{
		return true;
	}
	if (CheckCollisionPointRec(LeftPoint(), enemyRect))
	{
		return true;
	}
	if (CheckCollisionPointRec(RightPoint(), enemyRect))
	{
		return true;
	}
	return false;
}