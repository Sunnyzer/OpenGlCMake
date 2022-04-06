#include "Transform.h"
#include <glm\ext\matrix_transform.hpp>

Transform::Transform()
{
	matrix = glm::mat4(1);
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
}

void Transform::AddPosition(glm::vec3 _pos)
{
	matrix = glm::translate(matrix, _pos);
	position = matrix[3];
}

void Transform::SetPosition(glm::vec3 _pos)
{
	matrix[3][0] = _pos.x;
	matrix[3][1] = _pos.y;
	matrix[3][2] = _pos.z;
}

void Transform::SetRotation(float _angle,glm::vec3 _axis)
{
	matrix = glm::rotate(matrix, _angle, _axis);
	rotation.x = matrix[0][3];
	rotation.y = matrix[1][3];
	rotation.z = matrix[2][3];
}

void Transform::SetScale(glm::vec3 _scale)
{
	matrix = glm::scale(matrix, _scale);
	scale.x = matrix[0][0];
	scale.y = matrix[1][1];
	scale.z = matrix[2][2];
}