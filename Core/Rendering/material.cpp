#include "material.h"
#include "resource_manager.h"

std::vector<Material*> Material::_materials;

Material::Material(float specular_intensity, float specular_exponent,
						const std::string& diffuse_texture,
						const std::string& normal_texture,
						const std::string& disp_texture,
						float disp_scale, float disp_offset)
{
	_materials.push_back(this);

	addFloat(MATERIAL_SPECULAR_INTENSITY, specular_intensity);
	addFloat(MATERIAL_SPECULAR_EXPONENT, specular_exponent);
	addFloat(MATERIAL_DISP_SCALE, disp_scale);
	addFloat(MATERIAL_DISP_BIAS, disp_scale / 2.0f * (disp_offset - 1.0f));

	addTexture(MATERIAL_DIFFUSE_TEXTURE, Texture(diffuse_texture));
	addTexture(MATERIAL_NORMAL_TEXTURE, Texture(normal_texture));
	addTexture(MATERIAL_DISP_TEXTURE, Texture(disp_texture));
}

Material::Material(float specular_intensity, float specular_exponent,
					const Texture& diffuse_texture,
					const std::string& normal_texture,
					const std::string& disp_texture,
					float disp_scale, float disp_offset)
{
	_materials.push_back(this);

	addFloat(MATERIAL_SPECULAR_INTENSITY, specular_intensity);
	addFloat(MATERIAL_SPECULAR_EXPONENT, specular_exponent);
	addFloat(MATERIAL_DISP_SCALE, disp_scale);
	addFloat(MATERIAL_DISP_BIAS, disp_scale / 2.0f * (disp_offset - 1.0f));

	addTexture(MATERIAL_DIFFUSE_TEXTURE, diffuse_texture);
	addTexture(MATERIAL_NORMAL_TEXTURE, Texture(normal_texture));
	addTexture(MATERIAL_DISP_TEXTURE, Texture(disp_texture));
}

Material::~Material()
{
}

bool Material::hasTexture(const std::string& key)
{
	return textureMap.find(key) != textureMap.end();
}

Texture& Material::getTexture(const std::string& key)
{
	return textureMap.at(key);
}

glm::vec3& Material::getVector(const std::string& key)
{
	return vectorMap.at(key);
}

float Material::getFloat(const std::string& key)
{
	if (floatMap.find(key) != floatMap.end())
	{
		return floatMap.at(key);
	}

	return 0.0f;
}

void Material::_load_textures()
{
	int num = _materials.size();
	
	for (int i = 0; i < num; i++)
	{
		if (!_materials[i]->hasTexture(MATERIAL_NORMAL_TEXTURE))
		{
			_materials[i]->addTexture(MATERIAL_NORMAL_TEXTURE, Texture(DEFAULT_NORMAL_TEXTURE));
		}

		if (!_materials[i]->hasTexture(MATERIAL_DISP_TEXTURE))
		{
			_materials[i]->addTexture(MATERIAL_DISP_TEXTURE, Texture(DEFAULT_DISP_TEXTURE));
		}
	}

	TextureResource::_load_all();
}