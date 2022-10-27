#pragma once

#include "../component.h"
#include "../delegates.h"
#include "../transform.h"

class SceneComponent : public GameComponent
{
public:
	Transform transform;

	MulticastDelegate<SceneComponent*> CollisionStartEvent;
	MulticastDelegate<SceneComponent*> CollisionEndEvent;

	SceneComponent(Game& game);

	Transform* GetTransform();
	void SetParent(GameComponent* parent, bool initial = false);
};