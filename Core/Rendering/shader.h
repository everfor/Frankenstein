#pragma once

#include "transform.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>

// GLSL shader uniform types
#define FLOAT_TYPE					"float"
#define INT_TYPE					"int"
#define VEC_TYPE					"vec"
#define MAT_TYPE					"mat"
#define SAMPLER_TYPE				"sampler2D"
#define BASE_LIGHT_TYPE				"BaseLight"
#define DIRECTIONAL_LIGHT_TYPE		"DirectionalLight"
#define ATTENUATION_TYPE			"Attenuation"
#define POINT_LIGHT_TYPE			"PointLight"
#define SPOT_LIGHT_TYPE				"SpotLight"
// Keywords
#define UNIFORM_KEYWORD				"uniform"
#define STRUCT_KEYWORD				"struct"
#define SEMICOLON_KEYWORD			";"
#define LEFT_BRACKET_KEYWORD		"{"
#define RIGHT_BRACKET_KEYWORD		"}"
#define SPACE_KEYWORD				" "
// Uniforms
#define UNIFORM_MVP					"MVP"
#define UNIFORM_MODEL				"model"
#define UNIFORM_EYE_POS				"eyePos"
#define UNIFORM_SPEC_INTENSITY		"specularIntensity"
#define UNIFORM_SPEC_EXP			"specularExponent"
#define UNIFORM_AMBIENT_LIGHT		"ambientIntensity"
#define UNIFORM_DIRECTIONAL_LIGHT	"directionalLight"
#define UNIFORM_POINT_LIGHT			"pointLight"
#define UNIFORM_SPOT_LIGHT			"spotLight"
#define UNIFORM_DISP_SCALE			"dispScale"
#define UNIFORM_DISP_BIAS			"dispBias"
#define UNIFORM_DIFFUSE_SAMPLER		"diffuse"
#define UNIFORM_NORMAL_SAMPLER		"normalMap"
#define UNIFORM_DISP_SAMPLER		"dispMap"

// Forward declaration
class Camera;
class Material;
class BaseLight;
class DirectionalLight;
class PointLight;
class SpotLight;

class Shader
{
	public:
		static enum _shader_type
		{
			AMBIENT_LIGHT,
			DIRECTIONAL_LIGHT,
			POINT_LIGHT,
			SPOT_LIGHT
		};
		virtual ~Shader();
		// Shaders
		void addVertexShader(const std::string& text);
		void addFragmentShader(const std::string& text);
		void addGeometryShader(const std::string& text);
		void compileAllShaders();
		void updateUniforms(Transform *transform, Camera *camera, Material *material);
		void bind();
		// Lightings
		void setLight(BaseLight* new_light) { light = new_light; };
		// Factory
		static Shader* GetShader(_shader_type type, BaseLight* light);
	protected:
		Shader(_shader_type shader_type, const std::string& vertex_shader, const std::string& fragment_shader);
	private:
		// private methods
		void addUniformWithType(const std::string& type, const std::string& name);
		void addProgram(const std::string& text, GLenum type);
		void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error);
		// Uniforms
		void addAllUniforms(const std::string& text);
		void addUniform(const std::string& uniform, const std::string& type);
		void setUniformi(const std::string& uniform, const GLint value);
		void setUniformf(const std::string& uniform, const GLfloat value);
		void setUniform(const std::string& uniform, const glm::vec3& value);
		void setUniform(const std::string& uniform, const glm::mat4& value);
		void setUniform(const std::string& uniform, BaseLight& base);
		void setUniform(const std::string& uniform, DirectionalLight& directionalLight);
		void setUniform(const std::string& uniform, PointLight& pointLight);
		void setUniform(const std::string& uniform, SpotLight& light);
		// Members
		_shader_type type;
		// Uniforms binded (Format: name, (type, id))
		std::map<std::string, std::pair<std::string, GLuint>> uniforms;
		GLuint program;
		unsigned int shaderCount;
		GLuint shaders[3];
		BaseLight* light;
		// User defined structs in GLSL shader (Format: struct, member(type, name))
		static void _add_uniform_structs(const std::string& text);
		static std::map<std::string, std::multimap<std::string, std::string>> _uniform_structs;
		// Factory
		static std::map<_shader_type, std::unique_ptr<Shader>> _shaders;
};