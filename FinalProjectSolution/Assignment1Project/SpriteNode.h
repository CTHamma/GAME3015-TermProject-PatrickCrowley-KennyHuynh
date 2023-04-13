#pragma once
#include "Entity.hpp"
#include "StateIdentifiers.hpp"
#include <string>

class SpriteNode :
    public Entity
{
public:
	enum Type
	{
		Title,
		MenuBG,
		Pause,
		Desert
	};

public:
	SpriteNode(Type type, Game* game, States::ID id);
	unsigned int	getID();

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();

	Type			mType;
	std::string		mSprite;
};
