#pragma once
#include <cstdio>
#include <string>
#include <enet\enet.h>

class ENet
{
public:
    ~ENet();
    static int Initialize();
    virtual void Update() = 0;
    virtual void SendMessageNet(ENetEvent _event,int _id) = 0;
    virtual void Menu(int _key, std::string* _message) = 0;
    ENetHost* host;
    ENetEvent event;
};
