#include "rendering_engine.h"
#include "forward_ambientshader.h"
#include "forward_directionalshader.h"
#include "forward_pointshader.h"

RenderingEngine::RenderingEngine(Camera& init_camera) :
					mainCamera(init_camera)
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
	object.render(ForwardAmbientShader::GetShader(glm::vec3(0.2, 0.2, 0.2)), &getMainCamera());

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	object.render(ForwardDirectionalShader::GetShader(DirectionalLight(BaseLight(glm::vec3(1, 1, 1), 0.8f), glm::vec3(1, -1, 0))), &getMainCamera());
	object.render(ForwardPointShader::GetShader(PointLight(BaseLight(glm::vec3(0, 1, 0), 0.5f), glm::vec3(-1, 1, 1), 0, 0, 1)), &getMainCamera());
	object.render(ForwardPointShader::GetShader(PointLight(BaseLight(glm::vec3(1, 0, 0), 0.5f), glm::vec3(1, 1, 1), 0, 0, 1)), &getMainCamera());

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
