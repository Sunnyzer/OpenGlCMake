#pragma once
#include <cstdio>
#include <string>
#include <enet\enet.h>
#include "../Action.h"
//#include "World.h"

#define ServerReplicated(Net) if(Net) if(Net->GetNetType() == NetType::Client) return;
#define ClientReplicated(Net) if(Net) if(Net->GetNetType() == NetType::Server) return; 
#define BothReplicated(Net) if(Net) if(Net->GetNetType() == NetType::None) return; 

enum class NetType
{
    None,
    Client,
    Server,
    Both,
};

class ENet
{
public:
    virtual ~ENet();
    static int Initialize();
    virtual void Update() = 0;
    virtual void SendBroadcastPacket(bool _reliable, NetType _send, int _flags, const char* _dataStr) = 0;
    NetType GetNetType() const { return netType; }
    Action<ENetPacket*> OnReceive;
protected:
    ENetHost* host = nullptr;
    ENetEvent event = ENetEvent();
    NetType netType;
};
