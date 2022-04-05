#include "MonoBehaviour.h"

void MonoBehaviour::SetOwner(GameObject* _gameObject)
{
	gameObject = _gameObject;
	Start();
}