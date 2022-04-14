#pragma once
#include <cstdio>
#include <string>
#include <enet\enet.h>
#include "../Action.h"

class ENet
{
public:
    ~ENet();
    static int Initialize();
    virtual void Update() = 0;
    virtual void SendBroadcastPacket(bool _reliable, int _flags, const char* _dataStr) = 0;
    ENetHost* host = nullptr;
    Action<ENetPacket*> OnReceive;
    ENetEvent event = ENetEvent();
};
