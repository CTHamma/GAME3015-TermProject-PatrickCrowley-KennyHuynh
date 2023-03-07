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
	


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
};

struct AircraftMover
{
	AircraftMover(float vx, float vy) :
		velocity(vx, vy)
	{
	}
	void operator() (SceneNode& node, const GameTimer dt)
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.setVelocity(velocity.x, velocity.y);
	}
	XMFLOAT2 velocity;
};

