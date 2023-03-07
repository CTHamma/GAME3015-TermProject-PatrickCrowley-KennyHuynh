#pragma once
class Player
{
public:
	void handleEvent(CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
};