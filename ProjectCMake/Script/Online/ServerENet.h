#pragma once
#include "ENet.h"
#include <vector>
#include "../Action.h"
 
class ServerENet : public ENet
{
public:
    ServerENet(int _port);
	void BroadcastPacket(bool _reliable,int _flags, const char* _dataStr);
    virtual void Update() override;
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

