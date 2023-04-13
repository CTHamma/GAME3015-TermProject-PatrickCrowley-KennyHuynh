#pragma once
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "State.hpp"
#include "../Common/GameTimer.h"
#include "StateIdentifiers.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context, States::ID id);

	void		draw();
	bool		update(const GameTimer& dt);
	bool		handleEvent();
	void		buildScene();
	void		adaptPlayerVelocity();
	CommandQueue& getCommandQueue();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	Aircraft*							mEnemy;
	CommandQueue						mCommandQueue;
	States::ID mState;
};
