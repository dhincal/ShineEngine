#pragma once
#include <GLAD/glad.h>
#include "GLFW/glfw3.h"
#include "Renderer/RenderContext.h"

class EngineContext
{
public:
	RenderContext Renderer;

	EngineContext();
	void Init_GLFW();
	void StartWindow(int width, int height, const char* title);
	void StartRender();
	void SetRenderEvent(void (EventFn)())
	{
		RenderEvent = EventFn;
	}
	
	~EngineContext();
	

private:
	GLFWwindow* m_window;
	void (*RenderEvent)();

	

};

