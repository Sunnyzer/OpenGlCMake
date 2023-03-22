#pragma once
#include "Factory.h"
#include "MonoBehaviour.h"
#include "ENet.h"
#include "json.hpp"
#include <Collider.h>

class Marble;
class ServerENet;

class MarbleControl : public MonoBehaviour
{

public:
	MarbleControl();
	~MarbleControl() override;
	void AddBall(Marble* _object);
	void RemoveMarble(Marble* _object);
	void Shoot();
protected:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;
private:
	void SetMarble();

	void DestroyMarble(Collider::HitResult _hitResult);
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
	MonoBehaviour* Clone()
	{
		return new MarbleControl(*this);
	}
};
REGISTERFACTORY(MonoBehaviour, MarbleControl);