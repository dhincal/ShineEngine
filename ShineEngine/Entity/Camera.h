#pragma once
#include "../stdafx.h"

#include "../Renderer/Shader.h"

#include "GLM/mat4x4.hpp"
#include "GLM/common.hpp"
#include "GLM/vec3.hpp"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>



class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0,0,-1.0f);
	glm::vec3 Up = glm::vec3(0, 1.0f, 0);

	int width;
	int height;

	float speed = 0.1f;
	float sensivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	void PerspectiveMatrix(float FOVdeg, float nearPlane, float farPlane);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();

private:
	glm::mat4 viewMat;
	glm::mat4 projMat;
	
};
/*


public:

	Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	glm::vec3* GetPositionPointer();

	void Refresh();

	void SetRotation(glm::vec3& eulerAngles);
	void Rotate(glm::vec3 rot);

	void SetPosition(glm::vec3 pos);
	void Translate(glm::vec3 pos);


private:
	glm::mat4 m_view;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::quat m_Quat;


*/
