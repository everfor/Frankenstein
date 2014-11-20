#pragma once

#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class CoreEngine;

class Camera : public Component
{
	public:
		Camera(float init_fov, float init_asp, float init_znear, float init_zfar);
		virtual ~Camera();
		// Other things
		float getFov() { return fov; };
		void setFov(float new_fov) { fov = new_fov; };
		float getAsp() { return aspect; };
		void setAsp(float new_asp) { aspect = new_asp; };
		float getZNear() { return zNear; };
		void setZNear(float new_znear) { zNear = new_znear; };
		float getZFar() { return zFar; };
		void setZFar(float new_zfar) { zFar = new_zfar; };
		// Projection
		glm::mat4& getCameraProjection();
		// Override
		void addToEngine(CoreEngine *engine) override;
	private:
		float fov;
		float aspect;
		float zNear;
		float zFar;
		glm::mat4 projection;
};

