#pragma once

#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class CoreEngine;

class Camera : public Component
{
	public:
		Camera(float init_fov, float init_asp, float init_znear, float init_zfar);
		virtual ~Camera();
		// Other things
		float getFov() { return fov; };
		void setFov(float new_fov) { fov = new_fov; projection = glm::perspective(fov, aspect, zNear, zFar); };
		float getAsp() { return aspect; };
		void setAsp(float new_asp) { aspect = new_asp; projection = glm::perspective(fov, aspect, zNear, zFar); };
		float getZNear() { return zNear; };
		void setZNear(float new_znear) { zNear = new_znear; projection = glm::perspective(fov, aspect, zNear, zFar); };
		float getZFar() { return zFar; };
		void setZFar(float new_zfar) { zFar = new_zfar; projection = glm::perspective(fov, aspect, zNear, zFar); };
		// Projection
		void setCameraProjection(const glm::mat4& new_projection) { projection = new_projection; };
		glm::mat4& getCameraViewProjection();
		// Override
		void addToEngine(CoreEngine *engine) override;
	private:
		float fov;
		float aspect;
		float zNear;
		float zFar;
		glm::mat4 projection;
		glm::mat4 view_projection;
};

