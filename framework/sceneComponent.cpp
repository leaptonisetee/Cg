#include "pch.h"

SceneComponent::SceneComponent(Game& game) : GameComponent(game)
{

}

Transform* SceneComponent::GetTransform()
{
	return &transform;
}

void SceneComponent::SetParent(GameComponent* parent, bool initial)
{
	if (parent != nullptr && CanBeChildOf(parent))
	{
		this->parent = parent;

		auto parentTransform = parent->GetTransform();

		if (parentTransform != nullptr && !initial)
		{
			auto newPos = transform.GetAbsolutePosition() - parentTransform->GetAbsolutePosition();
			transform.position = newPos;
		}

		transform.parent = parentTransform;
	}
}