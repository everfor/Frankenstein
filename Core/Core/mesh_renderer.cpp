#include "mesh_renderer.h"
#include "phong_shader.h"

MeshRenderer::MeshRenderer(Mesh *init_mesh, Material *init_material) :
			mesh(std::unique_ptr<Mesh>(init_mesh)), material(std::unique_ptr<Material>(init_material))
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(Transform& transform, Camera& camera)
{
	Shader *shader = PhongShader::GetShader();
	shader->bind();
	shader->updateUniforms(transform, camera, *(material.get()));
	mesh.get()->draw();
}
