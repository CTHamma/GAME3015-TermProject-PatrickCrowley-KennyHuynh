#pragma once
#include "Command.hpp"
#include "CommandQueue.hpp"
#include <map>
#include "SceneNode.hpp"

class Player
{
public:
	Player();
	void handleEvent(CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	
	float		playerSpeed = 1;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};
	void					assignKey(Action action, char key);
	char					getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	std::map<char, Action>		mKeyBinding;
	std::map<Action, Command>	mActionBinding;
};