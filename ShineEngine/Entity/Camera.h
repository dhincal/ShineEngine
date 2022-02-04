#pragma once

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

	Camera();

	glm::mat4 GetViewMatrix();
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
	
};

