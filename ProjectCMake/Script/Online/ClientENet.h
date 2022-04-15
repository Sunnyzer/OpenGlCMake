#pragma once
#include "ENet.h"

class ClientENet : public ENet
{
public:
	ClientENet(const char* _ip, int _port);
	void SendPseudo(bool _reliable, const char* _pseudo);
	void SendBroadcastPacket(bool _reliable, NetType _send, int _flags, const char* _pseudo);
private:
	void SendPacket(bool _reliable, const char* _dataStr);
	void SetupClient();
	void ConnectClient(const char* _ip, int _port);
	void DisconnectClient();
	virtual void Update() override;
	ENetPeer* peer;
};

