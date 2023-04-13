#include "SpriteNode.h"
#include "Game.hpp"
#include "StateIdentifiers.hpp"

SpriteNode::SpriteNode(Type type, Game* game, States::ID id) : Entity(game, id)
, mType(type)
{
	switch (type)
	{
	case (Title):
		mSprite = "Title";
			break;
	case (MenuBG):
		mSprite = "Menu";
			break;
	case (Pause):
		mSprite = "Pause";
		break;
	case (Desert):
		mSprite = "Desert";
		break;
	default:
		mSprite = "Desert";
		break;

	}
}

unsigned int SpriteNode::getID()
{
	switch (mType)
	{
	case (Title):
		return States::Title;
	case (MenuBG):
		return States::Menu;
	case (Pause):
		return States::Pause;
	case (Desert):
		return States::Game;
	}
}





void SpriteNode::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(50.0f, 1.0f, 10.0f)); // Changed Scale
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["planeGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["plane"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["plane"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["plane"].BaseVertexLocation;
	renderer->thisState = currentState;

	game->getRenderItems().push_back(std::move(render));
}
