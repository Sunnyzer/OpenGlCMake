#pragma once
#include <enet\enet.h>
#include <cstdio>

enum class ModeNet
{
    None,
    Server,
    Client
};

class ENet
{
public:
    int Initialize();
    void SetupServer();
    void SetupClient();
    void ConnectClient();
    void Update();
    void SendPacket(bool _reliable, const char* _dataStr);
    void BroadcastPacket(bool _reliable, const char* _dataStr);
    bool IsClientConnected()
    {
        return IsClient() && client;
    }
    bool IsClient()
    {
        return mode == ModeNet::Client;
    }

    void DisconnectClient()
    {

    }
    ENetHost* client;
    ENetHost* server;
    ENetPeer* peer;
    ENetEvent event;
    ModeNet mode;
};
