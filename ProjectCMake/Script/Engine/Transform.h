#pragma once
#include <glm\ext\matrix_transform.hpp>

class Transform
{
public:
	Transform();
	void AddPosition(glm::vec3 _pos);
	void AddRotation(float _angle, glm::vec3 _axis);
	void SetPosition(glm::vec3 _pos);
	void SetRotation(glm::vec3 _rot);
	void SetScale(glm::vec3 _scale);
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 matrix;
};