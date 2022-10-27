#include "pch.h"

BoxColliderComponent::BoxColliderComponent(Game& game, Vector3 extents) : GameComponent(game), box(BoundingBox(Vector3::Zero, extents))
{

}

void BoxColliderComponent::UpdatePosition()
{
	auto transform = parent->GetTransform();

	if (transform != nullptr)
	{
		box.Center = transform->GetAbsolutePosition();
	}
}

void BoxColliderComponent::Init()
{
	game.boxColliders.push_back(this);
	UpdatePosition();
}

void BoxColliderComponent::Update(float deltaTime)
{
	UpdatePosition();
}

void BoxColliderComponent::Destroy()
{
	utils::remove_by_value(game.boxColliders, this);
}

bool BoxColliderComponent::Intersects(BoxColliderComponent* other)
{
	return previousIntersections.contains(other);
}

void BoxColliderComponent::CheckCollision(BoxColliderComponent* other)
{
	auto parent = dynamic_cast<SceneComponent*>(this->parent);
	auto otherParent = dynamic_cast<SceneComponent*>(other->parent);

	if (parent != nullptr && otherParent != nullptr)
	{
		bool intersects = box.Intersects(other->box);

		if (intersects && !this->Intersects(other))
		{
			previousIntersections.insert(other);
			parent->CollisionStartEvent.Broadcast(otherParent);
		}
		else if (!intersects && this->Intersects(other))
		{
			previousIntersections.erase(other);
			parent->CollisionEndEvent.Broadcast(otherParent);
		}
	}
}