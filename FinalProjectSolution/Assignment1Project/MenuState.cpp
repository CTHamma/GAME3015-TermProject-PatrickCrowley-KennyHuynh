#pragma region step 11
#include "MenuState.hpp"
//#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Game.hpp"


MenuState::MenuState(StateStack& stack, Context context, States::ID id)
	: State(stack, context)
	, mState(States::Menu)
	, mSceneGraph(new SceneNode(context.window, id))
	, mGame(context.window)
	, mBackground(nullptr)
	//, mPlayerAircraft(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
{
}

void MenuState::draw()
{
	Game& window = *getContext().window;
	mBackground->draw();

	//if (mShowText)
	//	window.draw(mText);
}

bool MenuState::update(const GameTimer& dt)
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

bool MenuState::handleEvent()
{
	// If any key is pressed, trigger the next screen
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		mGame->SetStateID(States::Title);
	}

	return true;
}
void MenuState::buildScene()
{
	//std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	//mPlayerAircraft = player.get();
	//mPlayerAircraft->setPosition(0, 3.5, 0.0);
	//mPlayerAircraft->setWorldRotation(-0.25, 0, 0);
	//mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	////mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	//mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<SpriteNode> menuScreen(new SpriteNode(SpriteNode::MenuBG, mGame, States::Menu));
	mBackground = menuScreen.get();
	mBackground->setPosition(-5.9, 3.6, 0.0);
	mBackground->setScale(195.0, 4.0, 1.0);
	mBackground->setWorldRotation(0.2, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(menuScreen));

	mSceneGraph->build();
}
#pragma endregion
