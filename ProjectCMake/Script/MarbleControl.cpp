#include "MarbleControl.h"
#include "Input.h"
#include "MovementMarble.h"
#include "GameObject.h"
#include <Script/Marble.h>

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	currentMarble = nullptr;
}

void MarbleControl::Start()
{
	Input::BindInput(GLFW_KEY_V, this, &MarbleControl::ChangeBall);
	for (size_t i = 0; i < 10; i++)
	{
		Marble* _marble = GameObject::Instanciate<Marble>();
		AddBall(_marble);
	}
}

void MarbleControl::Update(float deltaTime)
{
	MovementMarble movement;
	double _sprintValue = Input::FlipFlop<double>(GLFW_KEY_LEFT_SHIFT, 5.0f, 1.0f);
	if (!marbles[currentIndex])return;
	movement.InputMovement(marbles[currentIndex]->gameObject, (deltaTime/ 10.0) * _sprintValue);
}


void MarbleControl::ChangeBall()
{
	++currentIndex;
	if (currentIndex >= marbles.size())
		currentIndex = 0;
	currentMarble = marbles[currentIndex];
}

void MarbleControl::AddBall(Marble* _object)
{
	marbles.push_back(_object);
}
