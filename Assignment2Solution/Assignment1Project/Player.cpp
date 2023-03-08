#include "Player.h"

Player::Player()
{
	mKeyBinding['W'] = MoveUp;
	mKeyBinding['A'] = MoveLeft;
	mKeyBinding['S'] = MoveDown;
	mKeyBinding['D'] = MoveRight;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
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
	for (auto pair : mKeyBinding)
	{
		if (GetAsyncKeyState(pair.first) & 0x8000) {// && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::initializeActions()
{
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed, 0.f));
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f, 0.f));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f, 0.f));
}


