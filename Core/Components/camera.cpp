#include "camera.h"
#include "transform.h"
#include "core_engine.h"
#include "rendering_engine.h"
#include "audio_engine.h"
#include "movement.h"

Camera::Camera(float init_fov, float init_asp, float init_znear, float init_zfar) :
fov(init_fov), aspect(init_asp), zNear(init_znear), zFar(init_zfar)
{
	projection = glm::perspective(init_fov, (float)init_asp, init_znear, init_zfar);
}

Camera::~Camera()
{
}

glm::mat4& Camera::getCameraViewProjection()
{
	glm::vec3 forward = glm::normalize(getTransform()->getTransformedForward());

	view_projection = projection * glm::lookAt(getTransform()->getTransformedTranslation(), getTransform()->getTransformedTranslation() + forward, UP_DIR);

	return view_projection;
}

void Camera::addToEngine(CoreEngine *engine)
{
	engine->getRenderingEngine()->addCamera(this);
	engine->getAudioEngine()->setListener(this);
}