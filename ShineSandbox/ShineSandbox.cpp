#include <iostream>
#include "EngineContext.h"

EngineContext engineContext;
Shader* sh;

void OnRender()
{
}

int main()
{


	engineContext.Init_GLFW();

	engineContext.SetRenderEvent(OnRender);
	engineContext.StartWindow(640, 480, "Hello Engine");

	float vertices[] = {
			0.5f, 0.0f,   0.4f,
			0.0f, 0.5f,   0.4f,
		   -0.5f, 0.0f,   0.4f,
	};
	unsigned int indices[] = {
		0,1,2
	};

	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(1);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 3);
	sh = new Shader("res/default.shader");


	engineContext.Renderer.AddObject(&va, &vb, &ib, sh);

	engineContext.StartRender();
}


