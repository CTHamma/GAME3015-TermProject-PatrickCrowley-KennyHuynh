#include "Player.h"

Player::Player()
{
	mKeyBinding['W'] = MoveUp;
	mKeyBinding['A'] = MoveLeft;
	mKeyBinding['S'] = MoveDown;
	mKeyBinding['D'] = MoveRight;

	Command command;
	command.action = derivedAction<Aircraft>(AircraftMover(0.0f, playerSpeed, 0.0f));
	command.category = Category::PlayerAircraft;

	mActionBinding[MoveUp] = command;
}

void Player::handleEvent(CommandQueue& commands)
{
	//if (event.type == char::Event::KeyPressed)
	//{
	//	// Check if pressed key appears in key binding, trigger command if so
	//	auto found = mKeyBinding.find(event.key.code);
	//	if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
	//		commands.push(mActionBinding[found->second]);
	//}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		/*Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = AircraftMover(-playerSpeed, 0.f, 0.0f);
		commands.push(moveLeft);*/
	}
}
