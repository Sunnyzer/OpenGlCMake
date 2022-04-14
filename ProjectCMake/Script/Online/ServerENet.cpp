#include "ServerENet.h"
#include <iostream>

using namespace std;

ServerENet::ServerENet(int _port)
{
    SetupServer(_port);
}

void ServerENet::SetupServer(int _port)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = _port;
    host = enet_host_create(&address, 32, 2, 0, 0);
    if (host == NULL)
        cout << "An error occurred while trying to create a server host" << endl;
    else
        cout << "Server Create" << endl;
}

void ServerENet::BroadcastPacket(bool _reliable, int _flags, const char* _dataStr)
{
    if (!host)return;
    ENetPacket* packet = enet_packet_create(_dataStr, strlen(_dataStr) + 1, _reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
    packet->flags = _flags;
    enet_host_broadcast(host, 0, packet);
    enet_host_flush(host);
}

void ServerENet::Update()
{
    if (!host)return;
    enet_host_service(host, &event, 16);
    string _message;
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
        _message = "A new client connected : ";
        _message = _message.insert(_message.size(), to_string(event.peer->connectID));
        cout << endl << _message << endl;
        break;
    case ENET_EVENT_TYPE_RECEIVE:
        switch (event.packet->flags)
        {
        case 0:
            OnReceive.Invoke(event.packet);
            enet_packet_destroy(event.packet);
            break;
        case 1:
            ServerENet::Profil _profil;
            _profil.id = event.peer->connectID;
            _message = (const char*)event.packet->data;
            _profil.pseudo = (const char*)event.packet->data;
            profils.push_back(_profil);
            _message = _message.insert(_message.size()," Logged !!!");
            cout << endl << _message << endl;
            BroadcastPacket(false, 0,_message.c_str());
            break;
        case 2:
            OnReceive.Invoke(event.packet);
            enet_packet_destroy(event.packet);
            break;
        }
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        for (size_t i = 0; i < profils.size(); i++)
        {
            if (profils[i].id == event.peer->connectID)
            {
                string _messageDisconnected = profils[i].pseudo;
                _messageDisconnected = _messageDisconnected.insert(_message.size(), " disconnected");
                cout << endl << _messageDisconnected << endl;
                BroadcastPacket(false, 0, _messageDisconnected.c_str());
            }
        }
        event.peer->data = NULL;
        break;
    }
}

void ServerENet::SendBroadcastPacket(bool _reliable, int _flags, const char* _dataStr)
{
    BroadcastPacket(_reliable, _flags, _dataStr);
}
