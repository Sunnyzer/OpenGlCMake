#pragma once
#include "ENet.h"

class ClientENet : public ENet
{
public:
	ClientENet(const char* _ip, int _port);
private:
	void SetupClient();
	void ConnectClient(const char* _ip, int _port);
	void DisconnectClient();
	void SendPacket(bool _reliable, const char* _dataStr);
	void SendPseudo(bool _reliable, const char* _pseudo);
	virtual void SendMessageNet(ENetEvent _event, int _id) override;
	virtual void Menu(int _key, std::string* _message) override;
	virtual void Update() override;
	ENetPeer* peer;
};

