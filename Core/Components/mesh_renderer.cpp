#include "mesh_renderer.h"
#include "shader.h"

MeshRenderer::MeshRenderer(Mesh *init_mesh, Material *init_material) :
			mesh(init_mesh), material(init_material)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(Shader *shader, Camera *camera)
{
	shader->bind();
	shader->updateUniforms(getTransform(), camera, (material));
	mesh->draw();
}
