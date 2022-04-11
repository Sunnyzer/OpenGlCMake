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
    cout << "PSEUDO: ";
    string _pseudo;
    cin >> _pseudo;
    int hostService = enet_host_service(host, &event, 5000);
    if (hostService > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        cout << "Connection succeeded." << endl;
        SendPseudo(false, _pseudo.c_str());
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
void ClientENet::SendMessageNet(ENetEvent _event, int _id)
{
    cout << ((_event.peer->host == host) ? "Server : " : " ") << _event.packet->data << endl;
    enet_packet_destroy(_event.packet);
}

void ClientENet::SendPacket(bool _reliable, const char* _dataStr)
{
    ENetPacket* packet = enet_packet_create(_dataStr, strlen(_dataStr) + 1, _reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
    packet->flags = 0;
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}
void ClientENet::Menu(int _key, std::string* _message)
{
    bool bContinue = true;
    string myMsg;
    size_t size = _message->size();
    Update();
    _key = toupper(_key);
    switch (_key)
    {
    case VK_ESCAPE:
        bContinue = false;
        break;
    case VK_RETURN:
        if (size >= 100 || size <= 0) return;
        SendPacket(false, _message->c_str());
        cout << endl << "Message : ";
        break;
    case VK_F1:
        DisconnectClient();
        break;
    case VK_F2:
        string ip;
        cout << "IP: ";
        cin >> ip;
        ConnectClient(ip.c_str(), 1233);
        break;
    }
}

void ClientENet::Update()
{
    enet_host_service(host, &event, 100);
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
        cout << endl <<"A new client connected : " << event.peer->connectID << endl;
        break;
    case ENET_EVENT_TYPE_RECEIVE:
        switch (event.packet->flags)
        {
        case 0:
            cout << endl;
            SendMessageNet(event, event.peer->connectID);
            break;
        case 1:
            cout << endl << event.packet->data << " Logged" << endl;
            break;
        }
        break;
    case ENET_EVENT_TYPE_DISCONNECT:
        cout << endl << "une deconnexion a ete detecter" << endl;
        event.peer->data = NULL;
        break;
    }
}
