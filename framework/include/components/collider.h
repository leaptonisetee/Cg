#pragma once

#include "../component.h"
#include "../delegates.h"

#include <d3d11.h>
#include <SimpleMath.h>
#include <unordered_set>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class BoxColliderComponent : public GameComponent
{
private:
	std::unordered_set<BoxColliderComponent*> previousIntersections;

	void UpdatePosition();

public:
	BoundingBox box;
	
	BoxColliderComponent(Game& game, Vector3 extents);
	void Init();
	void Update(float deltaTime);
	void Destroy();

	bool Intersects(BoxColliderComponent* other);
	void CheckCollision(BoxColliderComponent* other);
};