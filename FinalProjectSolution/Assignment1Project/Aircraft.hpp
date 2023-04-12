#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);
	unsigned int	getCategory();


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
	
};

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz) :
		velocity(vx, vy, vz)
	{
	}
	void operator() (SceneNode& node, const GameTimer& dt) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity.x, velocity.y, velocity.z);
	}
	XMFLOAT3 velocity;
};

