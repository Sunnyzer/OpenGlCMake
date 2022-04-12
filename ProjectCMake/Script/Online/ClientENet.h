#pragma once
#include "ENet.h"

class ClientENet : public ENet
{
public:
	ClientENet(const char* _ip, int _port);
	void SendPacket(bool _reliable, const char* _dataStr);
	void SendPseudo(bool _reliable, const char* _pseudo);
private:
	void SetupClient();
	void ConnectClient(const char* _ip, int _port);
	void DisconnectClient();
	virtual void Update() override;
	ENetPeer* peer;
};

