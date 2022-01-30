#include "stdafx.h"
#include "EngineContext.h"
#include <iostream>

#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"


#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GLM/mat4x4.hpp"


#include "ImGui/imgui.h"
#include "ImGui_Impl/imgui_impl_glfw.h"
#include "ImGui_Impl/imgui_impl_opengl3.h"

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

}

void EngineContext::StartRender()
{
	glEnable(GL_DEPTH_TEST);
	float x=0, y=0, z=0;
	while (!glfwWindowShouldClose(m_window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0.09f, 0.21f, 1.0f);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		RenderEvent();

		Renderer.DrawAll();



		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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