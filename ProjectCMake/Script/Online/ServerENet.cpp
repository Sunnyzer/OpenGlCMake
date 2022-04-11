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
    {
        cout << "An error occurred while trying to create a server host" << endl;
    }
    else
    {
        cout << "Server Create" << endl;
    }
}

void ServerENet::BroadcastPacket(bool _reliable, const char* _dataStr)
{
    ENetPacket* packet = enet_packet_create(_dataStr, strlen(_dataStr) + 1, _reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
    enet_host_broadcast(host, 0, packet);
    enet_host_flush(host);
}

void ServerENet::Update()
{
    enet_host_service(host, &event, 100);
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
            cout << endl;
            SendMessageNet(event, event.peer->connectID);
            break;
        case 1:
            ServerENet::Profil _profil;
            _profil.id = event.peer->connectID;
            string _message = (const char*)event.packet->data;
            _profil.pseudo = (const char*)event.packet->data;
            profils.push_back(_profil);
            _message = _message.insert(_message.size()," Logged !!!");
            cout << endl << _message << endl;
            BroadcastPacket(false, _message.c_str());
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
                BroadcastPacket(false, _messageDisconnected.c_str());
            }
        }
        event.peer->data = NULL;
        break;
    }
}

void ServerENet::SendMessageNet(ENetEvent _event, int _id)
{
    for (size_t i = 0; i < profils.size(); i++)
    {
        if (profils[i].id == _id)
        {
            cout << profils[i].pseudo << " : " << _event.packet->data << endl;
            std::string _pseudo = profils[i].pseudo;
            std::string _message = _pseudo.insert(_pseudo.size(), " : ");
            _message = _message.insert(_message.size(), (const char*)_event.packet->data);
            BroadcastPacket(false , _message.c_str());
            enet_packet_destroy(_event.packet);
            return;
        }
    }
}

void ServerENet::Menu(int _key, string* _message)
{
    Update();
    _key = toupper(_key);
    switch (_key)
    {
    case VK_RETURN:
        if (_message->size() >= 100) return;
        BroadcastPacket(false, _message->c_str());
        cout << endl << "Message : ";
        break;
    }
}
