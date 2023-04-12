#pragma once
#include "SceneNode.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"

class World 
{
public:
	explicit							World(Game* window);
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
	SceneNode*							mPlayerAircraft;
	SceneNode*							mBackground;
	SceneNode*							mEnemy;
	CommandQueue						mCommandQueue;
};
