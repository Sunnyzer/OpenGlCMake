#pragma once
#include <cstdio>
#include <string>
#include <enet\enet.h>
#include "../Action.h"
//#include "World.h"

#define ServerReplicated(Net) if(Net) if(Net->netType == NetType::Client) return;
#define ClientReplicated(Net) if(Net) if(Net->netType == NetType::Server) return; 
#define BothReplicated(Net) if(Net) if(Net->netType == NetType::None) return; 

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
    ~ENet();
    static int Initialize();
    virtual void Update() = 0;
    virtual void SendBroadcastPacket(bool _reliable, NetType _send, int _flags, const char* _dataStr) = 0;
    ENetHost* host = nullptr;
    Action<ENetPacket*> OnReceive;
    ENetEvent event = ENetEvent();
    NetType netType;
};
