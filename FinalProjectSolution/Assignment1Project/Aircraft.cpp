#include "Aircraft.hpp"
#include "Game.hpp"
#include "Category.hpp"

Aircraft::Aircraft(Type type, Game* game, States::ID id) : Entity(game, id)
	, mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

unsigned int Aircraft::getCategory()
{
	switch (mType)
	{
	case (Eagle):
		return Category::PlayerAircraft;
	case (Raptor):
		return Category::AlliedAircraft;
	}
}

void Aircraft::drawCurrent() const
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = game->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = game->mCurrFrameResource->MaterialCB->Resource();

	if (aircraftRenderer != nullptr)
	{
		game->getCommandList()->IASetVertexBuffers(0, 1, &aircraftRenderer->Geo->VertexBufferView());
		game->getCommandList()->IASetIndexBuffer(&aircraftRenderer->Geo->IndexBufferView());
		game->getCommandList()->IASetPrimitiveTopology(aircraftRenderer->PrimitiveType);

		//step18
		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(game->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(aircraftRenderer->Mat->DiffuseSrvHeapIndex, game->mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + aircraftRenderer->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + aircraftRenderer->Mat->MatCBIndex * matCBByteSize;

		//step19
		game->getCommandList()->SetGraphicsRootDescriptorTable(0, tex);
		game->getCommandList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		game->getCommandList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		game->getCommandList()->DrawIndexedInstanced(aircraftRenderer->IndexCount, 1, aircraftRenderer->StartIndexLocation, aircraftRenderer->BaseVertexLocation, 0);
	}
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	aircraftRenderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
