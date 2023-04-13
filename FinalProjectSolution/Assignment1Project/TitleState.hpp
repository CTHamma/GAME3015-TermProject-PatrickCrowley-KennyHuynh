#pragma once
#pragma region step 7
#include "State.hpp"
#include "../Common/GameTimer.h"
#include "CommandQueue.hpp"
#include "SpriteNode.h"
#include "StateIdentifiers.hpp"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context, States::ID id);

	void		draw();
	bool		update(const GameTimer& dt);
	bool		handleEvent();
	void		buildScene();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*				mGame;
	SpriteNode*			mBackground;
	SpriteNode*			mText;
	//Aircraft*			mPlayerAircraft;
	//sf::Text			mText;

	float				mTextEffectTime;
	bool				mShowText;

	//GameTimer&			mTextEffectTime;
	SceneNode*			mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	XMFLOAT4							mWorldBounds;
	States::ID mState;
};
#pragma endregion
