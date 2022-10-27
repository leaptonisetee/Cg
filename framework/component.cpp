#include "pch.h"

bool GameComponent::CanBeChildOf(GameComponent* parent)
{
	GameComponent* current = parent;
	while (current != nullptr)
	{
		if (current == this) return false;
		current = current->parent;
	}

	return true;
}

void GameComponent::InitChildren()
{
	for (auto child : children)
	{
		child->Init();
		child->InitChildren();
	}
}

void GameComponent::DrawChildren()
{
	for (auto child : children)
	{
		child->Draw();
		child->DrawChildren();
	}
}

void GameComponent::UpdateChildren(float deltaTime)
{
	for (auto child : children)
	{
		child->Update(deltaTime);
		child->UpdateChildren(deltaTime);
	}
}

void GameComponent::DestroyChildren()
{
	for (auto child : children)
	{
		child->Destroy();
		child->DestroyChildren();
	}
}

Transform* GameComponent::GetTransform()
{
	return nullptr;
}

GameComponent* GameComponent::GetParent()
{
	return parent;
}

void GameComponent::SetParent(GameComponent* parent, bool initial)
{
	if (CanBeChildOf(parent))
	{
		this->parent = parent;
	}
}