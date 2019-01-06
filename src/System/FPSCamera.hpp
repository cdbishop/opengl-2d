#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"

#include <glm/gtc/type_ptr.hpp>

class Application;

class FPSCamera : public Camera {
public:
	FPSCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float aspectRatio, float near, float far, Application* app);

	void Update() override;

private:
	Application * _app;
	glm::vec3 _forward;
	float _movementSpeed;

	float _pitch;
	float _yaw;
};