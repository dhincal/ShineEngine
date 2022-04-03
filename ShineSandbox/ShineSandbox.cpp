#include <iostream>
#include "EngineContext.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GLM/mat4x4.hpp"
#include <ImGui/imgui.h>

EngineContext engineContext;
Shader* sh;
glm::mat4 mvp = glm::mat4(1.0f);

glm::vec3 modelPos;
glm::vec3 CamRot;

Camera cam;

void OnRender()
{
	sh->Bind();
	sh->SetUniformMat4x4("mvp", glm::value_ptr(mvp));


	glm::mat4 model = glm::translate(
		glm::mat4(1.0f),			// matrix to translate
		glm::vec3(modelPos.x, modelPos.y, modelPos.z)	// translation vector
	);
	glm::mat4 projection = glm::perspective(
		((float)640 / 480) / (16.0f / 9.0f), // FOV
		640.0f / 480.0f, // aspect ratio
		0.1f, //near
		10.0f //far
	);


	mvp = projection * cam.GetViewMatrix() * model;
	glm::vec3* pos = cam.GetPositionPointer();
	

	ImGui::Begin("Window 1");

	ImGui::Text("view = %.3f, %.3f ,%.3f", pos->x, pos->y, pos->z);

	ImGui::DragFloat3("Eye Pos", &pos->x, 0.005f);
	ImGui::DragFloat3("Model Pos", &modelPos[0],0.005f);
	ImGui::DragFloat3("Rotation ",&CamRot.x);

	ImGui::End();

	cam.SetRotation(CamRot);
	cam.Refresh();
	
}

int main()
{


	engineContext.Init_GLFW();

	engineContext.SetRenderEvent(OnRender);
	engineContext.StartWindow(640, 480, "Hello Engine");

	float Cube_Vertices[] = {
		// front			
		-1.0, -1.0,  1.0,	1.0, 0.0, 0.0,
		 1.0, -1.0,  1.0,	0.0, 1.0, 0.0,
		 1.0,  1.0,  1.0,	0.0, 0.0, 1.0,
		-1.0,  1.0,  1.0,	1.0, 1.0, 1.0,
		// back			
		-1.0, -1.0, -1.0,	1.0, 0.0, 0.0,
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

	IndexBuffer ib(indices, 36);
	sh = new Shader("res/shaders/Cube.shader");


	engineContext.Renderer.AddObject(&va, &vb, &ib, sh);

	engineContext.StartRender();
}


