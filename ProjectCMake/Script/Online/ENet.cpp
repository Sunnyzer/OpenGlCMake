#include "ENet.h"
#include <iostream>

using namespace std;

ENet::~ENet()
{
    enet_host_destroy(host);
}

int ENet::Initialize()
{
    if (enet_initialize() != 0)
    {
       cout << "An error occurred while initializing ENet" << endl;
        return 0;
    }
    atexit(enet_deinitialize);
    return 1;
}