#include "Transform.h"
#include <GL/glew.h>

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
	position += _pos;
}

void Transform::AddRotation(float _angle, glm::vec3 _axis)
{
	matrix = glm::rotate(matrix, _angle, _axis);
	rotation += _angle * _axis;
}

void Transform::SetPosition(glm::vec3 _pos)
{
	matrix = glm::translate(matrix, _pos - position);
	position = _pos;
}

void Transform::SetRotation(glm::vec3 _rot)
{
	matrix = glm::rotate(matrix, glm::radians(_rot.x - rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(_rot.y - rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(_rot.z - rotation.z), glm::vec3(0, 0, 1));
	rotation = _rot;
}

void Transform::SetScale(glm::vec3 _scale)
{
	glm::vec3 _avoidZero = glm::vec3(scale.x == 0 ? 1 : scale.x, scale.y == 0 ? 1 : scale.y, scale.z == 0 ? 1 : scale.z);
	glm::vec3 _finalScale = _scale / _avoidZero;
	scale = _scale;
	float _value = 0.00001f;
	if (_finalScale.x == 0)
	{
		_finalScale.x = _value / _avoidZero.x;
		scale.x = _value;
	}
	if (_finalScale.y == 0)
	{
		_finalScale.y = _value / _avoidZero.y;
		scale.y = _value;
	}
	if (_finalScale.z == 0)
	{
		_finalScale.z = _value / _avoidZero.z;
		scale.z = _value;
	}
	matrix = glm::scale(matrix, _finalScale);
}
