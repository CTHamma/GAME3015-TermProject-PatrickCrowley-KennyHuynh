#pragma once
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "Game.hpp"

#include <memory>


//namespace sf
//{
//	class RenderWindow;
//}

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Game& window, TextureHolder& textures, /*FontHolder& fonts,*/ Player& player);

		Game* window;
		TextureHolder* textures;
		//FontHolder* fonts;
		Player* player;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& dt) = 0;
	virtual bool		handleEvent(const CommandQueue& commands) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack* mStack;
	Context				mContext;
};