#include <iostream>
#include "EngineContext.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GLM/mat4x4.hpp"

EngineContext engineContext;
Shader* sh; 
glm::mat4 mvp;

void OnRender()
{
	//sh->Bind();
	//sh->SetUniformMat4x4("mvp", glm::value_ptr(mvp));
}

int main()
{


	engineContext.Init_GLFW();

	engineContext.SetRenderEvent(OnRender);
	engineContext.StartWindow(640, 480, "Hello Engine");

	/*float vertices[] = {
			0.5f, 0.0f,   0.4f,
			0.0f, 0.5f,   0.4f,
		   -0.5f, 0.0f,   0.4f,
	};
	unsigned int indices[] = {
		0,1,2
	};
	*/
	/*
		float Cube_Vertices[] = {
			// front			Colors
			-1.0, -1.0,  1.0,	1.0, 0.0, 0.0,
			 1.0, -1.0,  1.0,	0.0, 1.0, 0.0,
			 1.0,  1.0,  1.0,	0.0, 0.0, 1.0,
			-1.0,  1.0,  1.0,	1.0, 1.0, 1.0,
			// back				Colors
			-1.0, -1.0, -1.0,   1.0, 0.0, 0.0,
			 1.0, -1.0, -1.0,	0.0, 1.0, 0.0,
			 1.0,  1.0, -1.0,	0.0, 0.0, 1.0,
			-1.0,  1.0, -1.0,	1.0, 1.0, 1.0
		};
		unsigned int indices[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3
		};

		VertexArray va;
		VertexBuffer vb(Cube_Vertices, sizeof(Cube_Vertices));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 12);
		sh = new Shader("res/Cube.shader");

		glm::mat4 model = glm::translate(
			glm::mat4(1.0f),			// matrix to translate
			glm::vec3(0.0, 0.0, -4.0)	// translation vector
		);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0, 0.0, 0.0),	// eye
			glm::vec3(0.0, 0.0, 0.0),	// center
			glm::vec3(0.0, 1.0, 0.0)	// up vector
		);
	
		glm::mat4 projection = glm::perspective(
			((float)640 / 480) / (16.0f / 9.0f), // FOV
			640.0f / 480.0f, // aspect ratio
			0.1f, //near
			10.0f //far
		);
		mvp = projection * view * model;
	*/
	//engineContext.Renderer.AddObject(&va, &vb, &ib, sh);

	engineContext.StartRender();
}


