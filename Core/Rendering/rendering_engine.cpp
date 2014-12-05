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

	altCamera = new Camera(70, (float)Display::GetHeight() / (float)Display::GetWidth(), 0.01, 1000);
	altCameraObject = std::unique_ptr<Object>(new Object());
	altCameraObject.get()->addComponent(altCamera);
	//altCameraObject.get()->getTransform().setTranslation(0, 1, 0);

	setVector(RENDERING_ENGINE_AMBIENT_LIGHT, glm::vec3(0.2, 0.2, 0.2));
	setTexture(RENDERING_ENGINE_SHADOW_MAP, new Texture("shadow_map", GL_TEXTURE_2D, GL_RG32F, GL_RGBA, GL_LINEAR, true, GL_COLOR_ATTACHMENT0));
	setTexture(RENDERING_ENGINE_TEMP_TARGET, new Texture("temp_target", GL_TEXTURE_2D, GL_RG32F, GL_RGBA, GL_LINEAR, true, GL_COLOR_ATTACHMENT0));

	// Plane Object
	// Target texture for render to texture
	// And texture filtering
	planeMaterial = std::unique_ptr<Material>(new Material(1, 8, Texture("plane_texture", GL_TEXTURE_2D, GL_RG32F, GL_RGBA, GL_LINEAR, true, GL_COLOR_ATTACHMENT0)));
	planeTransform = std::unique_ptr<Transform>(new Transform());
	planeTransform.get()->setTranslation(0, 0, 0);
	planeTransform.get()->setScale(1, 1, 1);
	plane = std::unique_ptr<Mesh>(new Mesh("./res/models/plane.obj"));

	// Shadow map uniform data
	setFloat(RENDERING_ENGINE_SHADOW_MIN_VARIANCE, 0.0002);
	setFloat(RENDERING_ENGINE_LIGHT_BLEEDING_THRESHOLD, 0.05);
}

RenderingEngine::~RenderingEngine()
{
	std::map<std::string, Texture*>::iterator it = textures.begin();

	while (it != textures.end())
	{
		if (it->second != NULL)
		{
			delete it->second;
		}
		textures.erase(it);

		it = textures.begin();
	}
}

void RenderingEngine::applyFilter(Shader *shader, Texture *src, Texture *dest)
{
	if (dest == NULL)
	{
		Display::BindAsRenderTarget();
	}
	else
	{
		dest->bindAsRenderTarget();
	}

	setTexture(RENDERING_ENGINE_FILTER_TARGET, src);

	// Orthogonal projection with alt camera placed at origin facing forward
	altCamera->setCameraProjection(glm::mat4(1.0));
	altCamera->getTransform()->setTranslation(0, 0, 0);
	altCamera->getTransform()->setRotation(glm::quat());

	Camera *main_cam = getMainCamera();
	addCamera(altCamera);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->bind();
	shader->updateUniforms(planeTransform.get(), this, planeMaterial.get());
	plane->draw();

	// Restore
	addCamera(main_cam);
	setTexture(RENDERING_ENGINE_FILTER_TARGET, NULL);
}

void RenderingEngine::gaussBlur(Texture *target, float blur_amt)
{
	setVector(RENDERING_ENGINE_BLUR_SCALE, glm::vec3(1.0f / (1024.0f * blur_amt), 0.0f, 0.0f));
	applyFilter(Shader::GetShader(Shader::_shader_type::FILTER_GAUSS_BLUR, NULL), target, getTexture(RENDERING_ENGINE_TEMP_TARGET));

	setVector(RENDERING_ENGINE_BLUR_SCALE, glm::vec3(0.0f, 1.0f / (1024.0f * blur_amt), 0.0f));
	applyFilter(Shader::GetShader(Shader::_shader_type::FILTER_GAUSS_BLUR, NULL), getTexture(RENDERING_ENGINE_TEMP_TARGET), target);
}

void RenderingEngine::setTexture(const std::string& key, Texture *value)
{
	textures[key] = value;
}

void RenderingEngine::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderingEngine::render(Object& object)
{
	Display::BindAsRenderTarget();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	clearScreen();
	BaseLight light(getVector(RENDERING_ENGINE_AMBIENT_LIGHT));
	object.render(Shader::GetShader(Shader::_shader_type::AMBIENT_LIGHT, &light), this);

	// Apply shader for each kind of light
	for (int i = 0; i < lights.size(); i++)
	{
		Shadow *shadow = lights[i]->getShadow();
		getTexture(RENDERING_ENGINE_SHADOW_MAP)->bindAsRenderTarget();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		clearScreen();

		// Shadow calculation
		if (shadow != NULL)
		{
			// Set camera to the configuration of the shadow of the light
			altCamera->setCameraProjection(shadow->getProjection());
			altCamera->getTransform()->setTranslation(lights[i]->getTransform()->getTransformedTranslation());
			altCamera->getTransform()->setRotation(lights[i]->getTransform()->getTransformedRotation());

			lightMatrix = altCamera->getCameraViewProjection();

			Camera *main = getMainCamera();
			addCamera(altCamera);

			// Render the shadow map
			glCullFace(GL_FRONT);
			object.render(Shader::GetShader(Shader::_shader_type::SHADOW_MAP, NULL), this);
			glCullFace(GL_BACK);

			addCamera(main);

			//applyFilter(Shader::GetShader(Shader::_shader_type::FILTER_NULL, NULL), getTexture(RENDERING_ENGINE_SHADOW_MAP), getTexture(RENDERING_ENGINE_TEMP_TARGET));
			//applyFilter(Shader::GetShader(Shader::_shader_type::FILTER_NULL, NULL), getTexture(RENDERING_ENGINE_TEMP_TARGET), getTexture(RENDERING_ENGINE_SHADOW_MAP));
			
			// Apply gauss filter to shadow map to make shadow softer
			gaussBlur(getTexture(RENDERING_ENGINE_SHADOW_MAP), 0.4);
		}

		Display::BindAsRenderTarget();
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);

		object.render(lights[i]->getShader(), this);

		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
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