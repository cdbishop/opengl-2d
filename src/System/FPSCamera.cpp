#include "FPSCamera.hpp"

#include "Application.hpp"

#include <sstream>

FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, float aspectRatio, float near, float far, Application* application) 
	:Camera(position, position + forward, up, aspectRatio, near, far),
	_app(application),
	_forward(forward),
	_movementSpeed(0.005f),
	_pitch(0.0f),
	_yaw(-90.0f)
{
}

void FPSCamera::Update()
{
	float dt = _app->GetFrameDelta();

	_yaw += _app->MouseX() * 0.05f;
	_pitch -= _app->MouseY() * 0.05f;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	else if (_pitch < -89.0f)
		_pitch = -89.0f;

	_forward.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward.y = sin(glm::radians(_pitch));
	_forward.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	glm::normalize(_forward);

	/*std::wstringstream ss;
	ss << "yaw: " << _yaw << " _pitch: " << _pitch << std::endl;
	ss << "forward: (" << _forward.x << ", " << _forward.y << ", " << _forward.z << ")" << std::endl;
	OutputDebugString(ss.str().c_str());*/

	if (glfwGetKey(_app->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		_position += _movementSpeed * dt * _forward;
	} else if (glfwGetKey(_app->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		_position -= _movementSpeed * dt * _forward;
	}

	if (glfwGetKey(_app->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		_position -= glm::normalize(glm::cross(_forward, _up)) * dt * _movementSpeed;
	}
	else if (glfwGetKey(_app->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		_position += glm::normalize(glm::cross(_forward, _up)) * dt * _movementSpeed;
	}

	_target = _position + _forward;
	Camera::Update();
}
