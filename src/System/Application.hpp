#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <System/Scene.hpp>
#include <System/ShaderManager.hpp>
#include <system/SoundManager.hpp>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Application : public std::enable_shared_from_this<Application>
{
public:	
	virtual ~Application();

  Application(const Application&) = delete;
  Application& operator=(Application const&) = delete;

	void Run();

	void RegisterScene(const std::string& sceneName, std::shared_ptr<Scene> scene);
	void SetScene(const std::string& sceneName);

  template<typename T, typename... Args>
  void SetScene(Args... args) {    
    std::static_pointer_cast<T>(_scenes[T::Name])->SetArgs(std::forward<Args>(args)...);
    SetScene(T::Name);
  }

	std::shared_ptr<ShaderManager> GetShaderManager();
  std::shared_ptr<SoundManager> GetSoundManager();

	unsigned int GetWidth() const {
		return _width;
	}

	unsigned int GetHeight() {
		return _height;
	}

	float GetAspectRatio() {
		return static_cast<float>(_width) / static_cast<float>(_height);
	}

	float GetFrameDelta() {
		return _frameDelta;
	}

	float MouseX() {
		return _mouseDeltaX;
	}

	float MouseY() {
		return _mouseDeltaY;
	}

	void EnableDepthBuffer();
	void DisableDepthBuffer();

	GLFWwindow* GetWindow();

  std::shared_ptr<spdlog::logger> GetLogger() const {
    return _logger;
  }

  template<typename... Args>
  static std::shared_ptr<Application> Create(Args&&... args) {
    return std::shared_ptr<Application>(new Application(std::forward<Args>(args)...));
  }

private:
  Application(unsigned int width, unsigned int height);

	void Init();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(window));
		pApp->OnFrameBufferResize(width, height);
	}

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		Application* pApp = static_cast<Application*>(glfwGetWindowUserPointer(window));
		pApp->MouseMove(static_cast<float>(xpos), static_cast<float>(ypos));
	}

	void MouseMove(float xpos, float ypos);

	void OnFrameBufferResize(int width, int height);

	void Update();

	void PreRender();
	void Render();
	void PostRender();

private:
	unsigned int _width;
	unsigned int _height;

	float _lastMouseX;
	float _lastMouseY;

	bool _firstMouse;
	float _mouseDeltaX;
	float _mouseDeltaY;

	GLFWwindow* _window;
	bool _depthTestEnabled;

	std::string _currentScene;
	std::map<std::string, std::shared_ptr<Scene>> _scenes;

	std::shared_ptr<ShaderManager> _shaderManager;

	std::shared_ptr<spdlog::logger> _logger;

  std::shared_ptr<SoundManager> _soundManager;

	float _frameDelta;
	float _lastFrameTime;
};

