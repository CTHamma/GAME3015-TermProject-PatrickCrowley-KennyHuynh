#pragma once
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "../Common/GameTimer.h"
#include "CommandQueue.hpp"
#include "Command.hpp"

//#include <SFML/System/NonCopyable.hpp>
//#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack// : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(States::ID stateID);

	void				update(const GameTimer& dt);
	void				draw();
	void				handleEvent(CommandQueue& commands);

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;

	enum Action
	{
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};


private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();
	//std::map<char, Action>		mKeyBinding;
	//std::map<Action, Command>	mActionBinding;


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}




