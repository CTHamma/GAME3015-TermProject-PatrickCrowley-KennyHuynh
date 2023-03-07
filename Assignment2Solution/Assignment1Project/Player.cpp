#include "Player.h"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
#include <windows.h>
void Player::handleRealtimeInput(CommandQueue& commands)
{
	const float playerSpeed = 30.f;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(
		AircraftMover(-playerSpeed, 0.f));
		commands.push(moveLeft);
	}
}
