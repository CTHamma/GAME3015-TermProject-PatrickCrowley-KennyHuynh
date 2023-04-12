#include "SceneNode.hpp"
#include "Game.hpp"
#include "Category.hpp"

SceneNode::SceneNode(Type type, Game* game)
	: mChildren()
	, mParent(nullptr)
	, game(game)
{
	mWorldPosition = XMFLOAT3(0, 0, 0);
	mWorldScaling = XMFLOAT3(1, 1, 1);
	mWorldRotation = XMFLOAT3(0, 0, 0);
	mScrollSpeed = XMFLOAT3(0, 0, 0);
}

void SceneNode::attachChild(SceneNode* child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode*SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](SceneNode* p) { return p == &node; });
	assert(found != mChildren.end());

	SceneNode* result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(const GameTimer& gt)
{
	updateCurrent(gt);
	updateChildren(gt);
}

void SceneNode::updateCurrent(const GameTimer& gt)
{
	// Do nothing by default
}

void SceneNode::updateChildren(const GameTimer& gt)
{
	for (SceneNode* child : mChildren)
	{
		child->update(gt);
	}
}

void SceneNode::draw()
{
	drawCurrent();
	drawChildren();
}

void SceneNode::drawCurrent()
{
	//Empty for now
}

void SceneNode::drawChildren()
{
	for (SceneNode* child : mChildren)
	{
		child->draw();
	}
}

void SceneNode::build()
{
	buildCurrent();
	buildChildren();
}

void SceneNode::buildCurrent()
{
	//Empty for now
}

void SceneNode::buildChildren()
{
	for (SceneNode* child : mChildren)
	{
		child->build();
	}
}

XMFLOAT3 SceneNode::getWorldPosition() const
{
	return mWorldPosition;
}

void SceneNode::setPosition(float x, float y, float z)
{
	mWorldPosition = XMFLOAT3(x, y, z);
}

XMFLOAT3 SceneNode::getWorldRotation() const
{
	return mWorldRotation;
}

void SceneNode::setWorldRotation(float x, float y, float z)
{
	mWorldRotation = XMFLOAT3(x, y, z);
}

XMFLOAT3 SceneNode::getWorldScale() const
{
	return mWorldScaling;
}

void SceneNode::setScale(float x, float y, float z)
{
	mWorldScaling = XMFLOAT3(x, y, z);
}

//XMFLOAT3 SceneNode::getWorldVelocity() const
//{
//	return mScrollSpeed;
//}
//
void SceneNode::setVelocity(float x, float y, float z)
{
	XMFLOAT3 velocity = XMFLOAT3(x, y, z);
	mVelocity = velocity;
}

void SceneNode::setVelocity(XMFLOAT3 newVelocity)
{
	mVelocity = newVelocity;
}

XMFLOAT3 SceneNode::getVelocity() const
{
	return mVelocity;
}

void SceneNode::accelerate(float x, float y, float z)
{
	mVelocity.x += x;
	mVelocity.y += y;
	mVelocity.z += z;
}

void SceneNode::accelerate(XMFLOAT3 newAcceleration)
{
	mVelocity.x += newAcceleration.x;
	mVelocity.y += newAcceleration.y;
	mVelocity.z += newAcceleration.z;
}

unsigned int SceneNode::getCategory()
{
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, const GameTimer& dt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);

	// Command children
	for (SceneNode* child : mChildren)
		child->onCommand(command, dt);
}

XMFLOAT4X4 SceneNode::getWorldTransform() const
{
	XMFLOAT4X4 transform = MathHelper::Identity4x4();
	XMMATRIX T = XMLoadFloat4x4(&transform);

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		XMMATRIX Tp = XMLoadFloat4x4(&node->getTransform());
		T = Tp * T;
	}
	XMStoreFloat4x4(&transform, T);

	return transform;
}

XMFLOAT4X4 SceneNode::getTransform() const
{
	XMFLOAT4X4 transform;
	XMStoreFloat4x4(&transform, XMMatrixScaling(mWorldScaling.x, mWorldScaling.y, mWorldScaling.z) *
		XMMatrixRotationX(mWorldRotation.x) *
		XMMatrixRotationY(mWorldRotation.y) *
		XMMatrixRotationZ(mWorldRotation.z) *
		XMMatrixTranslation(mWorldPosition.x, mWorldPosition.y, mWorldPosition.z));
	return transform;
}

void SceneNode::move(float x, float y, float z)
{
	mWorldPosition.x += x;
	mWorldPosition.y += y;
	mWorldPosition.z += z;

	if (mWorldPosition.z <= -20.0f)
	{
		mWorldPosition.z = 40.0f;
	}
}
