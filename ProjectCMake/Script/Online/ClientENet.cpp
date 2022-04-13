#include "ClientENet.h"
#include <iostream>

using namespace std;

ClientENet::ClientENet(const char* _ip, int _port)
{
    SetupClient();
    ConnectClient(_ip, _port);
}
void ClientENet::SetupClient()
{
    host = enet_host_create(NULL, 1, 2, 0, 0);
    if (host == NULL)
    {
        cout << "An error occurred while trying to create a client host" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Client Create" << endl;
    }
}

void ClientENet::ConnectClient(const char* _ip, int _port)
{
    ENetAddress address;
    enet_address_set_host(&address, _ip);
    address.port = _port;
    peer = enet_host_connect(host, &address, 2, 0);
    if (peer == NULL)
    {
        cout << "No available peers for initiating an ENet connection" << endl;
    }
    int hostService = enet_host_service(host, &event, 5000);
    if (hostService > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        cout << "Connection succeeded." << endl;
        SendPseudo(false, "Nassim");
    }
    else
    {
        enet_peer_reset(peer);
        cout << "Connection failed." << endl;
    }
}
void ClientENet::DisconnectClient()
{
    ENetEvent event;
    enet_peer_disconnect(peer, 0);
    enet_host_service(host, &event, 3000);
    switch (event.type)
    {
    case ENET_EVENT_TYPE_RECEIVE:
        enet_packet_destroy(event.packet);
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        cout << "Disconnection succeeded." << endl;
        return;
    }
    enet_peer_reset(peer);
}
void ClientENet::SendPseudo(bool _reliable, const char* _pseudo)
{
    ENetPacket* packet = enet_packet_create(_pseudo, strlen(_pseudo) + 1, _reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
    packet->flags = 1;
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}

void ClientENet::SendPacket(bool _reliable, const char* _dataStr)
{
    ENetPacket* packet = enet_packet_create(_dataStr, strlen(_dataStr) + 1, _reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
    packet->flags = 0;
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}

void ClientENet::Update()
{
    enet_host_service(host, &event, 16);
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
        cout << endl <<"A new client connected : " << event.peer->connectID << endl;
        break;
    case ENET_EVENT_TYPE_RECEIVE:
        switch (event.packet->flags)
        {
        case 0:
            OnReceive.Invoke(event.packet);
            enet_packet_destroy(event.packet);
            break;
        case 1:
            cout << endl << event.packet->data << " Logged" << endl;
            enet_packet_destroy(event.packet);
            break;
        case 2:
            OnReceive.Invoke(event.packet);
            enet_packet_destroy(event.packet);
            break;
        }
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        cout << endl << "une deconnexion a ete detecter" << endl;
        event.peer->data = NULL;
        break;
    }
}
