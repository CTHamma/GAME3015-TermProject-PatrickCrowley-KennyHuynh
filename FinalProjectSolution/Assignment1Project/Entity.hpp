#pragma once
#include "SceneNode.hpp"
#include "StateIdentifiers.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* game, States::ID id);
	void				setVelocity(float x, float y, float z);
	void				setVelocity(XMFLOAT3 newVelocity);
	XMFLOAT3			getVelocity() const;

	void				accelerate(float x, float y, float z);
	void				accelerate(XMFLOAT3 newAcceleration);

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
};



