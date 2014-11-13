#include "rendering_engine.h"
#include "forward_ambientshader.h"

RenderingEngine::RenderingEngine(Camera& init_camera, glm::vec3& init_ambient) :
					mainCamera(init_camera), ambientLight(init_ambient)
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
	object.render(ForwardAmbientShader::GetShader(ambientLight), &getMainCamera());
}
