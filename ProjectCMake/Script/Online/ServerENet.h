#pragma once
#include "ENet.h"
#include <vector>
#include "../Action.h"

class ServerENet : public ENet
{
public:
    ServerENet(int _port);
    virtual ~ServerENet();
    virtual void Update() override;
    virtual void SendBroadcastPacket(bool _reliable, NetType _send,int _flags, const char* _dataStr) override;
	void BroadcastPacket(bool _reliable, int _flags, const char* _dataStr);
protected:
	void SetupServer(int _port);
	ENetHost* host;
    struct Profil
    {
        int id;
        const char* pseudo;
    };
    std::vector<Profil> profils;
};

