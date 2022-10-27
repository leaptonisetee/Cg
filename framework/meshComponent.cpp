#include "pch.h"

#include <wrl.h>

MeshComponent::MeshComponent(Game& game, Mesh* mesh) : GameComponent(game), mesh(mesh)
{

}

void MeshComponent::Draw()
{
	auto context = game.Render.Context;

	context->IASetInputLayout(mesh->layout.Get());
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetIndexBuffer(mesh->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, mesh->vertexBuffer.GetAddressOf(), mesh->strides, mesh->offsets);

	auto pixelShader = mesh->material->pixelShader.get();
	auto vertexShader = mesh->material->vertexShader.get();
	context->PSSetShader(pixelShader->shader.Get(), nullptr, 0);
	context->VSSetShader(vertexShader->shader.Get(), nullptr, 0);

	if (pixelShader->constBuffer != nullptr)
	{
		context->PSSetConstantBuffers(0, 1, pixelShader->constBuffer.GetAddressOf());
		pixelShader->UpdateConstBuffer(context);
	}

	if (vertexShader->constBuffer != nullptr)
	{
		context->VSSetConstantBuffers(0, 1, vertexShader->constBuffer.GetAddressOf());
		vertexShader->UpdateConstBuffer(context);
	}

	context->DrawIndexed(mesh->indexes.size(), 0, 0);
}