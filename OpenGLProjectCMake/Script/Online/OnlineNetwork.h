#pragma once
#include <string>
#include "Action.h"

class ENet;
enum class NetType;

class OnlineNetwork
{
private:
	OnlineNetwork();
public:
	~OnlineNetwork();
	static OnlineNetwork* onlineNetwork;
	Action<> OnNetworkSet;
	
	void SendPacket(NetType _netType, int flags, std::string _dataStr);
	void Update();
	void LoadClient();
	void LoadServer();

	inline ENet* GetNetwork() const { return networkLayer; }
private:
	ENet* networkLayer;
};