#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* game);
	void				setVelocity(float x, float y, float z);
	void				setVelocity(float vx, float vy);
	XMFLOAT3			getVelocity() const;

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
};

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz) :
		velocity(vx, vy, vz)
	{
	}
	void operator() (SceneNode& node, const GameTimer dt)
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.setVelocity(velocity.x, velocity.y, velocity.z);
	}
	XMFLOAT3 velocity;
};

