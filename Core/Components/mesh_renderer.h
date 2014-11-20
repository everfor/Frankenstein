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
		void render(Shader *shader, Camera *camera) override;
	private:
		Mesh *mesh;
		Material *material;
};

