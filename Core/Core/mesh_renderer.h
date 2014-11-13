#pragma once

#include "mesh.h"
#include "material.h"
#include "component.h"

#include <memory>

class MeshRenderer : public Component
{
	public:
		MeshRenderer(Mesh *init_mesh, Material *init_material);
		virtual ~MeshRenderer();
		void render(Shader *shader, Transform *transform, Camera *camera) override;
	private:
		std::unique_ptr<Mesh> mesh;
		std::unique_ptr<Material> material;
};

