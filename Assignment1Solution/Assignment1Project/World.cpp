#include "World.hpp"

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

void World::update(const GameTimer& gt)
{
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
	mPlayerAircraft->setPosition(0, 1, 0.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5, 0, 1);
	raptor->setScale(1.0, 1.0, 1.0);
	raptor->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0, 1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0, XM_PI, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> plane1(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane1.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(20.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane1));

	std::unique_ptr<SpriteNode> plane2(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane2.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 20.0);
	mBackground->setScale(20.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane2));

	std::unique_ptr<SpriteNode> plane3(new SpriteNode(SpriteNode(mGame)));
	mBackground = plane3.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 40.0);
	mBackground->setScale(20.0, 1.0, 20.0); // Made world larger by increasing scale
	mBackground->setVelocity(0.0f, 0.0f, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(plane3));

	mSceneGraph->build();
}
