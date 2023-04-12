#pragma once
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "Player.h"

#include <memory>


//namespace sf
//{
//	class RenderWindow;
//}

class StateStack;
class Player;
class Game;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context();
		Context(Game* window, Player& player);

		Game* window;
		Player& player;
	};


public:
	State(StateStack& stack, Context context);


	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& dt) = 0;
	virtual bool		handleEvent() = 0;
	virtual void		buildScene() = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;
	Context				mContext;

private:
	StateStack*			mStack;
};