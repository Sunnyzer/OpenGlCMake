#pragma once
#include <glm/glm.hpp>
#include "Action.h"

class Transform
{
public:
	Transform();
	void SetPosition(glm::vec3 _pos);
	void SetRotation(glm::vec3 _rotation);
	void SetScale(glm::vec3 _scale);
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Action<glm::vec3> OnPositionChange;
	Action<glm::vec3> OnScaleChange;
};