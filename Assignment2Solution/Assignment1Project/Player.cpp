#include "Player.h"
void Player::handleRealtimeInput(CommandQueue& commands)
{
	const float playerSpeed = 30.f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = AircraftMover(-playerSpeed, 0.f);
		commands.push(moveLeft);
	}
}
