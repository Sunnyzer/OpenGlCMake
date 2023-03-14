#include "MonoBehaviour.h"
#include "World.h"

MonoBehaviour::~MonoBehaviour()
{
	
}

void MonoBehaviour::SetOwner(GameObject* _gameObject)
{
	gameObject = _gameObject;
	Start();
}
