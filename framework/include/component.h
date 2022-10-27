#pragma once

#include <vector>

class Game;
struct Transform;

class GameComponent
{
protected:
	Game& game;
	GameComponent* parent = nullptr;
	std::vector<GameComponent*> children;

	GameComponent(Game& game) : game(game) { }

	bool CanBeChildOf(GameComponent* parent);


public:
	~GameComponent() { }

	virtual void Init() { }
	virtual void Draw() { }
	virtual void Update(float deltaTime) { }
	virtual void Destroy() { }

	void InitChildren();
	void DrawChildren();
	void UpdateChildren(float deltaTime);
	void DestroyChildren();

	template<typename TComponent, typename = std::enable_if_t<std::is_base_of_v<GameComponent, TComponent>>>
	TComponent* AddChild(TComponent* child) 
	{
		children.insert(children.end(), child);
		child->SetParent(this, true);

		return child;
	}

	virtual Transform* GetTransform();
	GameComponent* GetParent();
	virtual void SetParent(GameComponent* parent, bool initial = false);
};