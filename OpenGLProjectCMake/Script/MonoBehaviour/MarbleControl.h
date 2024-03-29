#pragma once
#include "MonoBehaviour.h"
#include "ENet.h"
#include "json.hpp"
#include <Collider.h>

class Marble;
class ServerENet;

class MarbleControl : public MonoBehaviour
{
    CLONE(MarbleControl);

public:
	MarbleControl();
	~MarbleControl() override;
	void AddBall(Marble* _object);
	void RemoveMarble(Marble* _object);
	void Shoot();
protected:
	virtual void OnGUI() override;
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;
private:
	void SetMarble();

	void DestroyMarble(HitResult _hitResult);
	void RemoveMarbleMono(MonoBehaviour* _mono);
	void AddReceiveInfoToOnReceive();
	void SetWall();
	void ReceiveInfo(ENetPacket* _receive);
	bool VerifAllMarbleStop(json::JSON& json);
	bool shoot = true;
	int currentIndex;
	size_t amountMarble;
	Marble* whiteMarble;
	std::vector<Marble*> marbles;
	float power = 75.0f;
};

REGISTERFACTORY(MonoBehaviour, MarbleControl)