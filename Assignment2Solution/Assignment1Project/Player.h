#pragma once
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"
class Player
{
public:
	void handleEvent(CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	//void PlayerInput
};