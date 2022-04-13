#pragma once
#include "MonoBehaviour.h"
#include <vector>

class Marble;

class MarbleControl : public MonoBehaviour
{
public:
	MarbleControl();
	void AddBall(Marble* _object);
	void Shoot();
protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	std::vector<Marble*> marbles;
	int currentIndex;
	Marble* whiteMarble;
	bool shoot = true;
};