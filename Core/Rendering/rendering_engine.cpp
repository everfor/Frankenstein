#include "rendering_engine.h"
#include "shader.h"
#include "base_light.h"

#include "object.h"

RenderingEngine::RenderingEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderingEngine::render(Object& object)
{
	clearScreen();
	BaseLight light(glm::vec3(0.2, 0.2, 0.2));
	object.render(Shader::GetShader(Shader::_shader_type::AMBIENT_LIGHT, &light), getMainCamera());

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	for (int i = 0; i < lights.size(); i++)
	{
		object.render(lights[i]->getShader(), getMainCamera());
	}

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void RenderingEngine::addLight(BaseLight *light)
{
	lights.push_back(light);
}

void RenderingEngine::clearLight()
{
	lights.clear();
}

void RenderingEngine::addCamera(Camera* camera)
{
	mainCamera = camera;
}