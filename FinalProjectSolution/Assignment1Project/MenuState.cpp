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
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	//, mPlayerAircraft(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
{
}

void MenuState::draw()
{
	Game& window = *getContext().window;
	mSceneGraph->draw();

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
	if (GetAsyncKeyState('1') & 0x8000)
	{
		mPlayerAircraft->setPosition(-0.3, 4.4, -1.8);
		number = 0;
		//mGame->SetStateID(States::Game);
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		mPlayerAircraft->setPosition(-0.3, 4.0, -1.8);
		number = 1;
		//mGame->SetStateID(States::Game);
	}

	// If enter key is pressed, trigger the next screen
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (number == 0)
		{
			mGame->SetStateID(States::Game);
		}
		else if (number == 1)
		{
			mGame->SetStateID(States::Title);
		}
	}

	return true;
}
void MenuState::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame, States::Menu));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(-0.3, 4.4, -1.8);
	mPlayerAircraft->setWorldRotation(-1, 0, 0);
	mPlayerAircraft->setScale(0.3, 0.3, 0.3);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<SpriteNode> menuScreen(new SpriteNode(SpriteNode::MenuBG, mGame, States::Menu));
	mBackground = menuScreen.get();
	mBackground->setPosition(-5.8, 4.0, -1.1);
	mBackground->setScale(195.0, 3.0, 1.0);
	mBackground->setWorldRotation(0.25, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(menuScreen));

	mSceneGraph->build();
}
#pragma endregion
