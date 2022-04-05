#include "MarbleControl.h"
#include "Input.h"
#include <Script\MovementMarble.h>
#include "GameObject.h"

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	currentMarble = nullptr;
}

void MarbleControl::Start()
{
	Input::BindInput(GLFW_KEY_V, this, &MarbleControl::ChangeBall);
}

void MarbleControl::Update(float deltaTime)
{
	MovementMarble movement;
	double _sprintValue = Input::FlipFlop<double>(GLFW_KEY_LEFT_SHIFT, 5.0f, 1.0f);
	if (!marbles[currentIndex])return;
	movement.InputMovement(marbles[currentIndex], (deltaTime/ 10.0) * _sprintValue);
}


void MarbleControl::ChangeBall()
{
	++currentIndex;
	if (currentIndex >= marbles.size())
		currentIndex = 0;
	currentMarble = marbles[currentIndex];
}

void MarbleControl::AddBall(GameObject* _object)
{
	marbles.push_back(_object);
}
