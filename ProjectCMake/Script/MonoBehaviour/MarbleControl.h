#pragma once
#include "ClientENet.h"
#include "MonoBehaviour.h"
#include "json.hpp"
#include <SphereCollider.h>

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

	void DestroyMarble(Collider::HitResult _hitResult);
	
	void AddReceiveInfoToOnReceive();
	void SetWall();
	void ReceiveInfo(ENetPacket* _receive);
	bool VerifAllMarbleStop(json::JSON& json);
	bool shoot = true;
	int currentIndex;
	size_t amountMarble;
	ServerENet* server;
	Marble* whiteMarble;
	std::vector<Marble*> marbles;
};