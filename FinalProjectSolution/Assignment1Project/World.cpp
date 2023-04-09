#include "World.hpp"

//

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)
{
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::update(const GameTimer& gt)
{
	mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);
	

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);
	adaptPlayerVelocity();

	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 3.5, 0.0);
	mPlayerAircraft->setWorldRotation(-0.25, 0, 0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5, 0, -1);
	raptor->setScale(1.0, 1.0, 1.0);
	//raptor->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0, -1);
	raptor2->setScale(1.0, 1.0, 1.0);
	//raptor2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> plane1(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane1.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane1));

	std::unique_ptr<SpriteNode> plane2(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane2.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 20.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane2));

	std::unique_ptr<SpriteNode> plane3(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane3.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 40.0);
	mBackground->setScale(100.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane3));

	mSceneGraph->build();
}

void World::adaptPlayerVelocity()
{
	XMFLOAT3 velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f) {
		velocity = XMFLOAT3(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f), 0.0f);
		mPlayerAircraft->setVelocity(velocity);
	}
}
