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
    ENetHost* host;
    Action<char*> OnReceive;
    ENetEvent event = ENetEvent();
};
