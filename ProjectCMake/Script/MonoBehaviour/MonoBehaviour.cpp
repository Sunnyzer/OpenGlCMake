#include "MonoBehaviour.h"
#include "World.h"

void MonoBehaviour::SetOwner(GameObject* _gameObject)
{
	gameObject = _gameObject;
	Start();
}