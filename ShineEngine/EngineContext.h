#pragma once
#include <GLAD/glad.h>
#include "GLFW/glfw3.h"
#include "Renderer/RenderContext.h"
#include "Entity/Camera.h"
#include "Entity/Input.h"


class EngineContext {

public:
	static EngineContext& getInstance()
	{ 
		// Guaranteed to be destroyed.
		// Instantiated on first use.
		static EngineContext instance;
		
		glfwInit();
		return instance;
		
	}

	void StartWindow(int width, int height, const char* title);
	void StartRender();
	void SetRenderEvent(void (EventFn)())
	{
		RenderEvent = EventFn;
	}

private:
	EngineContext():RenderEvent(), m_window() {}                    // Constructor? (the {} brackets) are needed here.
	~EngineContext()
	{
		glfwTerminate();
	}

	GLFWwindow* m_window;
	void (*RenderEvent)();


public:
	EngineContext(EngineContext const&) = delete;
	void operator=(EngineContext const&) = delete;
};