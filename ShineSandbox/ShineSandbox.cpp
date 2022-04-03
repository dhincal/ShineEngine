#include <iostream>
#include "EngineContext.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <ImGui/imgui.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Shader* sh;
Shader* sh_2;
glm::mat4 mvp = glm::mat4(1.0f);
glm::mat4 mvp_2 = glm::mat4(1.0f);

glm::vec3 modelPos;
glm::vec3 modelPos_2;
glm::vec3 CamRot;

Camera cam = Camera(640, 480, { 0,0,0 });

void sh1_PreRender();
void sh2_PreRender();

void OnRender()
{
	glm::vec3* pos = &cam.Position;
	

	ImGui::Begin("Window 1");

	ImGui::Text("view = %.3f, %.3f ,%.3f", pos->x, pos->y, pos->z);

	ImGui::DragFloat3("Eye Pos", &pos->x, 0.005f);
	ImGui::DragFloat3("Model Pos", &modelPos[0],0.005f);
	ImGui::DragFloat3("Model Pos 2", &modelPos_2[0],0.005f);
	ImGui::DragFloat3("Rotation ",&CamRot.x);

	ImGui::End();


	if (Input::getInstance().GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glm::vec2 mousePos = Input::getInstance().GetMousePosition();
		// Stores the coordinates of the cursor
		double mouseX = mousePos.x;
		double mouseY = mousePos.y;

		float sensitivity = 0.5f;
		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (cam.height / 2)) / cam.height;
		float rotY = sensitivity * (float)(mouseX - (cam.width / 2)) / cam.width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(cam.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(cam.Orientation, cam.Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, cam.Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			cam.Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		cam.Orientation = glm::rotate(cam.Orientation, glm::radians(-rotY), cam.Up);
	}
	


	
}

int main()
{
	EngineContext::getInstance().SetRenderEvent(OnRender);
	EngineContext::getInstance().StartWindow(640, 480, "Hello Engine");

	cam.PerspectiveMatrix(70,0.1f,100);

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
	sh_2 = new Shader("res/shaders/Cube.shader");

	sh->SetPreRenderEvent(sh1_PreRender);
	sh_2->SetPreRenderEvent(sh2_PreRender);

	RenderContext::getInstance().AddObject(&va, &vb, &ib, sh);
	RenderContext::getInstance().AddObject(&va, &vb, &ib, sh_2);

	EngineContext::getInstance().StartRender();
}



void sh1_PreRender() {
	glm::mat4 model = glm::translate(
		glm::mat4(1.0f),			// matrix to translate
		glm::vec3(modelPos.x, modelPos.y, modelPos.z)	// translation vector
	);

	mvp = cam.GetProjMatrix() * cam.GetViewMatrix() * model;

	sh->SetUniformMat4x4("mvp", glm::value_ptr(mvp));
	
}

void sh2_PreRender() {

	glm::mat4 model_2 = glm::translate(
		glm::mat4(1.0f),			// matrix to translate
		glm::vec3(modelPos_2.x, modelPos_2.y, modelPos_2.z)	// translation vector
	);
	mvp_2 = cam.GetProjMatrix() * cam.GetViewMatrix() * model_2;

	sh_2->SetUniformMat4x4("mvp", glm::value_ptr(mvp_2));
}
