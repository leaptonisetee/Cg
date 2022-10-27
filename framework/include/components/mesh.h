#pragma once

#include "../component.h"
#include "../mesh.h"

class MeshComponent : public GameComponent
{
private:
	std::unique_ptr<Mesh> mesh;

public:
	MeshComponent(Game& game, Mesh* mesh);
	~MeshComponent() = default;

	void Draw();
};