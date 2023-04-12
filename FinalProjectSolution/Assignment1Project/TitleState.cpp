#pragma region step 11
#include "TitleState.hpp"
//#include "Utility.hpp"
#include "ResourceHolder.hpp"


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mSceneGraph(new SceneNode(context.window))
	, mGame(context.window)
	, mBackground(nullptr)
	//, mPlayerAircraft(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
{
}

void TitleState::draw()
{
	Game& window = *getContext().window;
	mBackground->draw();

	//if (mShowText)
	//	window.draw(mText);
}

bool TitleState::update(const GameTimer& dt)
{
	//mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);
	//mTextEffectTime += dt.DeltaTime();

	//if (mTextEffectTime >= 0.5f)
	//{
	//	mShowText = !mShowText;
	//	mTextEffectTime = 0.0f;
	//}
	mSceneGraph->update(dt);

	return true;
}

bool TitleState::handleEvent()
{
	// If any key is pressed, trigger the next screen
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}
void TitleState::buildScene()
{
	//std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	//mPlayerAircraft = player.get();
	//mPlayerAircraft->setPosition(0, 3.5, 0.0);
	//mPlayerAircraft->setWorldRotation(-0.25, 0, 0);
	//mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	////mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	//mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<SpriteNode> background(new SpriteNode(SpriteNode::MenuBG, mGame));
	mBackground = background.get();
	mBackground->setPosition(0.0f, 0.0f, 0.0f);
	mBackground->setWorldRotation(0.0f, 0.0f, 0.0f);
	mSceneGraph->attachChild(std::move(background));

	mSceneGraph->build();
}
#pragma endregion
