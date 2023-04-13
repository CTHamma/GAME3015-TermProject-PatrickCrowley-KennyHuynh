#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "Command.hpp"
#include "CommandQueue.hpp"

class World 
{
public:
	explicit							World(Game* window, States::ID id);
	void								update(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();
	void								adaptPlayerVelocity();
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
};
