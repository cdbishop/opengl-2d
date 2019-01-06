#pragma once

class Application;

class Scene
{
public:
	Scene() {}

	void SetApp(Application* app) {
		_app = app;
	}	
	
	virtual ~Scene() { }

	virtual void Init() { }

	virtual void Update() { }

	virtual void Render() { }

protected:
	Application * GetApplication() {
		return _app;
	}

private:
	Application * _app;
};
