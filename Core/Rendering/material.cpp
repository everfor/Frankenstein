#include "material.h"


Material::Material(const Texture& init_texture, const glm::vec3& init_color, float init_specular_intensity, float init_specular_exp) :
			texture(init_texture), color(init_color), hasTexture(false), specularIntensity(init_specular_intensity), specularExponent(init_specular_exp)
{
}

Material::~Material()
{
}
