#include "stdafx.h"
#include "EngineContext.h"
#include <iostream>

#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

void CheckErrorInShader(unsigned int shaderId);

EngineContext::EngineContext()
	:RenderEvent(), m_window()
{
	Renderer = RenderContext();
}

EngineContext::~EngineContext()
{
	glfwTerminate();
}
void EngineContext::Init_GLFW()
{
	glfwInit();
}

void EngineContext::StartWindow(int width, int height, const char* title)
{

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return;
	}


}

void EngineContext::StartRender()
{

	//float vertices[] = {
	//  -0.5f, -0.5f,  0.7f, // sol alt
	//   0.5f, -0.5f,  0.5f,// sag alt
	//   0.5f,  0.5f,  0.1f,// sag ust
	//  -0.5f,  0.5f,  0.3f,// sol ust
	//};

	float Quad_vertices[] = {
	   0.2f, -0.2f,  0.7f, // sol alt
	   0.6f, -0.2f,  0.5f,// sag alt
	   0.6f,  0.2f,  0.1f,// sag ust
	   0.2f,  0.2f,  0.3f,// sol ust
	};

	unsigned int Quad_indices[] = {
		0,1,2,
		2,3,0
	};

	float Tri_vertices[] = {
		0.0f, 0.0f,
		-0.5f, 0.5f,
		-0.5f, 0.0f,
	};

	unsigned int Tri_indices[] = {
		0,1,2
	};




	


	VertexArray Quad_va;
	VertexBuffer Quad_vb(Quad_vertices, sizeof(Quad_vertices));
	Shader Quad_sh("res/VertexShader.osuruk", "res/FragmentShader.osuruk");


	VertexBufferLayout Quad_layout;
	Quad_layout.Push<float>(2);
	Quad_layout.Push<float>(1);
	Quad_va.AddBuffer(Quad_vb, Quad_layout);

	IndexBuffer Quad_ib(Quad_indices, 6);




	VertexArray Tri_va;
	VertexBuffer Tri_vb(Tri_vertices, sizeof(Tri_vertices));
	Shader Tri_sh("res/VertexShader.osuruk", "res/FragmentShader.osuruk");


	VertexBufferLayout Tri_layout;
	Tri_layout.Push<float>(2);
	Tri_va.AddBuffer(Tri_vb, Tri_layout);

	IndexBuffer Tri_ib(Tri_indices, 6);


	Tri_sh.Unbind();
	Tri_va.Unbind();
	Tri_vb.Unbind();

	Quad_sh.Unbind();
	Quad_va.Unbind();
	Quad_vb.Unbind();


	Renderer.AddObject(&Quad_va, &Quad_vb, &Quad_ib, &Quad_sh);
	Renderer.AddObject(&Tri_va, &Tri_vb, &Tri_ib, &Tri_sh);
	
	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0.09f, 0.21f, 1.0f);

		//RenderEvent();

		Quad_sh.Bind();
		//Quad_va.Bind();
		//Quad_vb.Bind();

		//Renderer.Draw(Quad_ib,Quad_va);
		
		Renderer.DrawAll();
		
		//Tri_sh.Unbind();
		//Tri_va.Unbind();
		//Tri_vb.Unbind();
		//Renderer.Draw(Tri_ib, Tri_va);
		//GL_Call(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));


		/*
			vao bind
			vbo bind
			ibo bind


			vao unbind;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		
		*/

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}




void CheckErrorInShader(unsigned int shaderId)
{
	int success;
	char infoLog[512];
	GL_Call(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GL_Call(glGetShaderInfoLog(shaderId, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

		__debugbreak();
	}
}