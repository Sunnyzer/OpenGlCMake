#include "Transform.h"

Transform::Transform()
{
}

void Transform::SetPosition(glm::vec3 _pos)
{
	position = _pos;
	OnPositionChange.Invoke(position);
}

void Transform::SetRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}

void Transform::SetScale(glm::vec3 _scale)
{
	scale = _scale;
	OnScaleChange.Invoke(scale);
}
