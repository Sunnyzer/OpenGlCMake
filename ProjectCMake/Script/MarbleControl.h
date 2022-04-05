#pragma once
#include "MonoBehaviour.h"
#include <vector>

class MarbleControl : public MonoBehaviour
{
public:
	MarbleControl();
	void ChangeBall();
	void AddBall(GameObject* _object);
protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	std::vector<GameObject*> marbles;
	int currentIndex;
	GameObject* currentMarble;
};