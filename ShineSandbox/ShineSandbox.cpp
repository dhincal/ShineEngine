#include <iostream>
#include "EngineContext.h"

EngineContext engineContext;

void OnRender()
{



}


int main()
{


	engineContext.Init_GLFW();

	engineContext.SetRenderEvent(OnRender);
	engineContext.StartWindow(640, 480, "Hello Engine");

	float vertices[] = {
			0.5f,0.0f,
			0.0f,0.5f,
			-0.5f,0.0f,
	};
	unsigned int indices[] = {
		0,1,2
	};

	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices,3);
	Shader sh("res/default.shader");


	engineContext.Renderer.AddObject(&va,&vb,&ib, &sh);

	engineContext.StartRender();



}


