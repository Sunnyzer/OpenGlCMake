#pragma once
#include "Action.h"
#include <string>

class ENet;
enum class NetType;

class OnlineNetwork
{
public:
	static OnlineNetwork* onlineNetwork;
	Action<> OnNetworkSet;
	ENet* networkLayer;
	void SendPacket(NetType _netType, int flags, std::string _dataStr);
	void Update();
	void LoadClient();
	void LoadServer();
private:
	OnlineNetwork();
};