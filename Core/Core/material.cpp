#include "material.h"


Material::Material(const Texture& init_texture, const glm::vec3& init_color) :
		texture(init_texture), color(init_color), hasTexture(false)
{
}

Material::~Material()
{
}
