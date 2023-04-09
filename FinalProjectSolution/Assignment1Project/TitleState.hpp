#pragma once
#pragma region step 7
#include "State.hpp"
#include "../Common/GameTimer.h"
#include "CommandQueue.hpp"
#include "SpriteNode.h"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& dt);
	virtual bool		handleEvent(CommandQueue& commands);


private:
	SpriteNode*			mBackgroundSprite;
	SpriteNode*			mText;
	//sf::Text			mText;

	float				mTextEffectTime;
	bool				mShowText;

	//GameTimer&			mTextEffectTime;
};
#pragma endregion
