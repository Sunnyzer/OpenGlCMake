#pragma once
#include "ENet.h"
#include <vector>

class ServerENet : public ENet
{
public:
    ServerENet(int _port);
protected:
	void SetupServer(int _port);
	void BroadcastPacket(bool _reliable, const char* _dataStr);
    virtual void Update() override;
    virtual void SendMessageNet(ENetEvent _event, int _id) override;
    virtual void Menu(int _key, std::string* _message) override;
	ENetHost* host;
    struct Profil
    {
        int id;
        const char* pseudo;
    };
    std::vector<Profil> profils;
};

