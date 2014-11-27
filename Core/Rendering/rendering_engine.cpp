#include "rendering_engine.h"
#include "shader.h"
#include "display.h"
#include "base_light.h"

#include "object.h"
#include "texture.h"
#include "mesh.h"
#include "material.h"

#include <GL/glew.h>

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

	altCamera = std::unique_ptr<Camera>(new Camera(70, Display::GetHeight() / Display::GetWidth(), 0.01, 1000));
	altCameraObject = std::unique_ptr<Object>(new Object());
	altCameraObject.get()->addComponent(altCamera.get());

	planeTexture = std::unique_ptr<Texture>(new Texture("", GL_TEXTURE_2D, GL_NEAREST, GL_COLOR_ATTACHMENT0));
	plane = std::unique_ptr<Mesh>(new Mesh("./res/models/plane.obj"));
	planeMaterial = std::unique_ptr<Material>(new Material(1, 8, *(planeTexture.get())));
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
	Display::BindAsRenderTarget();

	clearScreen();
	BaseLight light(glm::vec3(0.2, 0.2, 0.2));
	object.render(Shader::GetShader(Shader::_shader_type::AMBIENT_LIGHT, &light), this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	for (int i = 0; i < lights.size(); i++)
	{
		object.render(lights[i]->getShader(), this);
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