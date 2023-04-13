#include "Entity.hpp"

Entity::Entity(Game* game, States::ID id) : SceneNode(game, id), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(float x, float y, float z)
{
	XMFLOAT3 velocity = XMFLOAT3(x, y, z);
	mVelocity = velocity;
}

void Entity::setVelocity(XMFLOAT3 newVelocity)
{
	mVelocity = newVelocity;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(float x, float y, float z)
{
	mVelocity.x += x;
	mVelocity.y += y;
	mVelocity.z += z;
}

void Entity::accelerate(XMFLOAT3 newAcceleration)
{
	mVelocity.x += newAcceleration.x;
	mVelocity.y += newAcceleration.y;
	mVelocity.z += newAcceleration.z;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
