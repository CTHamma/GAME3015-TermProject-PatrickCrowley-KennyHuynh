#pragma once
#pragma region step 7
#include "State.hpp"
#include "../Common/GameTimer.h"
#include "CommandQueue.hpp"
#include "SceneNode.hpp"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);
	~TitleState();

	void		draw() override;
	bool		update(const GameTimer& dt) override;
	bool		handleEvent() override;
	void		buildScene() override;


private:
	SceneNode*			mBackgroundSprite;
	SceneNode*			mText;
	//sf::Text			mText;

	float				mTextEffectTime;
	bool				mShowText;

	//GameTimer&			mTextEffectTime;
	SceneNode*			mSceneGraph;
};
#pragma endregion
