#pragma region step 11
#include "PauseState.hpp"
//#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Game.hpp"

PauseState::PauseState(StateStack& stack, Context context, States::ID id)
	: State(stack, context)
	, mState(States::Pause)
	, mSceneGraph(new SceneNode(context.window, id))
	, mGame(context.window)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
{
}

bool PauseState::update(const GameTimer& dt)
{
	mSceneGraph->update(dt);

	return true;
}

bool PauseState::handleEvent()
{
	// If any key is pressed, trigger the next screen
	if (GetAsyncKeyState('R') & 0x8000)
	{
		mGame->SetStateID(States::Game);
	}
	return true;
}

void PauseState::draw()
{
	Game& window = *getContext().window;
	mSceneGraph->draw();
}

void PauseState::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame, States::Pause));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 3.5, 0.0);
	mPlayerAircraft->setWorldRotation(-0.25, 0, 0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame, States::Pause));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5, 0, -1);
	raptor->setScale(1.0, 1.0, 1.0);
	//raptor->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame, States::Pause));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0, -1);
	raptor2->setScale(1.0, 1.0, 1.0);
	//raptor2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> plane1(new SpriteNode(SpriteNode::Desert, mGame, States::Pause));
	mBackground = plane1.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mSceneGraph->attachChild(std::move(plane1));

	std::unique_ptr<SpriteNode> plane2(new SpriteNode(SpriteNode::Desert, mGame, States::Pause));
	mBackground = plane2.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 20.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mSceneGraph->attachChild(std::move(plane2));

	std::unique_ptr<SpriteNode> plane3(new SpriteNode(SpriteNode::Desert, mGame, States::Pause));
	mBackground = plane3.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 40.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mSceneGraph->attachChild(std::move(plane3));

	mSceneGraph->build();
}
