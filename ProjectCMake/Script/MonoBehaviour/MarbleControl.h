#pragma once
#include "MonoBehaviour.h"
#include "json.hpp"

class Marble;
class ServerENet;

class MarbleControl : public MonoBehaviour
{
public:
	MarbleControl();
	void AddBall(Marble* _object);
	void Shoot();
protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
private:
	void SetMarble();
	void SetWall();
	bool VerifAllMarbleStop(json::JSON& json);
	bool shoot = true;
	int currentIndex;
	size_t amountMarble;
	ServerENet* server;
	Marble* whiteMarble;
	std::vector<Marble*> marbles;
};