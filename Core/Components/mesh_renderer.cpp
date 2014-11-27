#include "mesh_renderer.h"
#include "rendering_engine.h"
#include "shader.h"

MeshRenderer::MeshRenderer(Mesh *init_mesh, Material *init_material) :
			mesh(init_mesh), material(init_material)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(Shader *shader, RenderingEngine *rendering_engine)
{
	shader->bind();
	shader->updateUniforms(getTransform(), rendering_engine, (material));
	mesh->draw();
}
