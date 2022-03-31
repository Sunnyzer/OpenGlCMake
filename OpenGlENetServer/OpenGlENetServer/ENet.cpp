#include "ENet.h"

int ENet::Initialize()
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return 0;
    }
    atexit(enet_deinitialize);
    return 1;
}

void ENet::SetupServer()
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 222;
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);
    if (server == NULL)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    mode = ModeNet::Server;
    //enet_host_destroy(server);
}

void ENet::SetupClient()
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (client == NULL)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }
    mode = ModeNet::Client;
    //enet_host_destroy(client);
}

void ENet::ConnectClient()
{
    ENetAddress address;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 222;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL)
    {
        fprintf(stderr,
            "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        puts("Connection to some.server.net:222 succeeded.");
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        puts("Connection to some.server.net:222 failed.");
    }
}

void ENet::Update()
{
    switch (event.type)
    {
    case ENET_EVENT_TYPE_CONNECT:
        printf("A new client connected from %x:%u.\n",
            event.peer->address.host,
            event.peer->address.port);
        /* Store any relevant client information here. */
        event.peer->data = (void*)"Client information";
        break;
    case ENET_EVENT_TYPE_RECEIVE:
        printf("A packet of length %u containing %s was received from %s on channel %u.\n",
            event.packet->dataLength,
            event.packet->data,
            event.peer->data,
            event.channelID);
        /* Clean up the packet now that we're done using it. */
        enet_packet_destroy(event.packet);

        break;

    case ENET_EVENT_TYPE_DISCONNECT:
        printf("%s disconnected.\n", event.peer->data);
        /* Reset the peer's client information. */
        event.peer->data = NULL;
    }
}

void ENet::SendPacket(bool _reliable, const char* _dataStr)
{

}

void ENet::BroadcastPacket(bool _reliable, const char* _dataStr)
{
}
