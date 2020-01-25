#include "Application.hpp"
#include <iostream>
#include <sstream>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

Application::Application(unsigned int width, unsigned int height)
  : _width(width),
  _height(height),
  _window(NULL),
  _lastFrameTime(0.0f),
  _frameDelta(0.0f),
  _lastMouseX(width / 2.0f),
  _lastMouseY(height / 2.0f),
  _mouseDeltaX(0.0f),
  _mouseDeltaY(0.0f),
  _firstMouse(true) {
  AllocConsole();
  _logger = spdlog::stdout_color_mt("console");
  _logger->set_level(spdlog::level::info);
  _logger->info("The Application has started");

  Init();

  _shaderManager = std::make_shared<ShaderManager>("./shaders");
  _soundManager = std::make_shared<SoundManager>();
}

Application::~Application() { glfwTerminate(); }

void Application::EnableDepthBuffer() {
  glEnable(GL_DEPTH_TEST);
  _depthTestEnabled = true;
}

void Application::DisableDepthBuffer() {
  glDisable(GL_DEPTH_TEST);
  _depthTestEnabled = false;
}

std::shared_ptr<GLFWwindow> Application::GetWindow() { return _window; }

void Application::Init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(_width, _height, "OpenGLTut", NULL, NULL), glfwDestroyWindow);
  if (_window == NULL) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW Window");
  }

  glfwMakeContextCurrent(_window.get());

  glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glViewport(0, 0, _width, _height);

  glfwSetWindowUserPointer(_window.get(), this);

  glfwSetFramebufferSizeCallback(_window.get(), framebuffer_size_callback);
  glfwSetCursorPosCallback(_window.get(), mouse_callback);

  int maxAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
  std::cout << "Max vertex attributes supported: " << maxAttributes
    << std::endl;
}

void Application::Run() {
  while (!glfwWindowShouldClose(_window.get())) {
    Update();
    Render();
  }
}

std::shared_ptr<ShaderManager> Application::GetShaderManager() {
  return _shaderManager;
}

std::shared_ptr<SoundManager> Application::GetSoundManager() {
  return _soundManager;
}

void Application::Update() {
  float currentFrameTime = static_cast<float>(glfwGetTime());
  _frameDelta = currentFrameTime - _lastFrameTime;
  _lastFrameTime = currentFrameTime;

  _currentScene->Update(_frameDelta);

  _mouseDeltaX = 0;
  _mouseDeltaY = 0;
  
  if (_nextScene) {
    ChangeScene();
  }
}

void Application::ChangeScene() {
  _currentScene = _nextScene;
  _nextScene = nullptr;
  _currentScene->Init();
}

void Application::MouseMove(float xpos, float ypos) {
  if (_firstMouse) {
    _lastMouseX = xpos;
    _lastMouseY = ypos;

    _firstMouse = false;
  }

  _mouseDeltaX = (xpos - _lastMouseX);
  _mouseDeltaY = (ypos - _lastMouseY);

  _lastMouseX = xpos;
  _lastMouseY = ypos;
}

void Application::OnFrameBufferResize(int width, int height) {
  glViewport(0, 0, width, height);
}

void Application::PreRender() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  GLbitfield clearFlags = GL_COLOR_BUFFER_BIT;
  if (_depthTestEnabled) clearFlags |= GL_DEPTH_BUFFER_BIT;

  glClear(clearFlags);
}

void Application::Render() {
  PreRender();
  _currentScene->Render();
  PostRender();
}

void Application::PostRender() {
  glfwSwapBuffers(_window.get());
  glfwPollEvents();
}
